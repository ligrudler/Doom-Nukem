/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 03:27:58 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 22:17:15 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		parse_line(t_parser *p, t_map *map, unsigned int i,
													char states[PS_MAX][PS_MAX])
{
	static int		(*lines_fts[PS_MAX])(t_map*, char**) = {new_mesh,
					new_vertex, new_txt_vertex, vertex_end,
					new_face, comment, mtllib, usemtl};
	unsigned int	j;

	j = 0;
	if (!(p->toks = ft_strsplit(p->lines[i], "\n\t\r "))
		|| get_line_type(p->toks[0], p, states))
		return (-1);
	if (p->state == PS_COMMENT)
	{
		ft_free_ctab(p->toks);
		return (0);
	}
	if (!(*init_parser()) && lines_fts[(int)p->state](map, p->toks))
		return (-1);
	ft_free_ctab(p->toks);
	return (0);
}

static int		load_map_data(t_map *map)
{
	t_triangle	new;
	t_mesh		*m;
	t_face		*f;
	int			i;
	int			j;

	i = -1;
	while (++i < map->nmesh && (j = -1))
	{
		if (!(m = dyacc(&map->meshs, i))
			|| (init_dynarray(&m->tris, sizeof(t_triangle), m->faces.nb_cells)))
			return (-1);
		m->type = 1;
		while (++j < m->faces.nb_cells && (f = dyacc(&m->faces, j)))
		{
			if (f->x - 1 >= map->pool.nb_cells || f->y - 1 >= map->pool.nb_cells
				|| f->z - 1 >= map->pool.nb_cells)
				return (-1);
			ft_memset(&new, 0, sizeof(t_triangle));
			if (!get_faces(&new, map, f, m) && push_dynarray(&m->tris, &new, 0))
				return (-1);
		}
		free_dynarray(&m->faces);
	}
	return (0);
}

static int		init_map_parser(t_map *map, t_parser *parser, char *path,
													char states[PS_MAX][PS_MAX])
{
	unsigned int	i;
	int				fd;
	int				len;

	i = 0;
	map->nmesh = 0;
	if ((fd = open(path, O_RDONLY)) == -1
		|| !(parser->file = read_file(fd, &len)) || len == 0
		|| !(parser->lines = ft_strsplit(parser->file, "\n"))
		|| init_dynarray(&map->pool, sizeof(t_vec3d), 0)
		|| init_dynarray(&map->txt_pool, sizeof(t_vec2d), 0)
		|| init_dynarray(&map->meshs, sizeof(t_mesh), 0))
		return (-1);
	parser->state = PS_COMMENT;
	while (parser->lines[i] && parser->state == PS_COMMENT)
	{
		if (parse_line(parser, map, i, states))
			return (-1);
		i++;
	}
	if (!parser->lines[i]
		|| (parser->state != PS_OBJ && parser->state != PS_MTLLIB))
		return (-1);
	return (0);
}

static int		err_msg(char *path, int i)
{
	ft_putstr_fd("Error parsing map ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" at line ", 2);
	ft_putnbr_fd(i, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int				parse_map(t_map *map, char *path, char states[PS_MAX][PS_MAX])
{
	t_parser		parser;
	unsigned int	i;

	i = 0;
	*init_parser() = true;
	if (init_map_parser(map, &parser, path, states))
		return (-1);
	*init_parser() = false;
	while (parser.lines[i])
	{
		if (parse_line(&parser, map, i, states))
			return (err_msg(path, i));
		i++;
	}
	if (load_map_data(map)
		|| !(map->stats = (bool*)malloc(sizeof(bool) * map->nmesh))
		|| !(map->stats_cpy = (bool*)malloc(sizeof(bool) * map->nmesh)))
		return (-1);
	free_dynarray(&map->pool);
	free_dynarray(&map->txt_pool);
	ft_free_ctab(parser.lines);
	munmap(parser.file, ft_strlen(parser.file));
	return (0);
}
