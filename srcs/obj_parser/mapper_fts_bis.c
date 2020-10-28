/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper_fts_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:07:33 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 21:11:44 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	no_texture(t_mesh *m)
{
	t_triangle	*t;
	int			i;

	i = 0;
	while (i < m->tris.nb_cells)
	{
		t = dyacc(&m->tris, i);
		if (t->textured)
			t->color = 0xff007f;
		i++;
	}
	return (0);
}

static void	set_sp_index(t_mesh *m)
{
	t_triangle	*t;
	int			i;

	i = 0;
	while (i < m->tris.nb_cells)
	{
		t = dyacc(&m->tris, i);
		t->sp = -1;
		i++;
	}
}

static void	attribute_texture_index(t_map *map, t_mesh *m)
{
	t_triangle	*t;
	int			i;

	i = 0;
	while (i < m->tris.nb_cells)
	{
		t = dyacc(&m->tris, i);
		if (t->textured)
			t->sp = t->textured ? map->txts.nb_cells - 1 : -1;
		i++;
	}
}

int			mapper_texture(t_env *env, t_mesh *m, char *tok)
{
	t_sprite	sprite;
	t_map		*map;
	char		*path;

	map = *current_map();
	if (ft_strlen(tok) <= 2)
		return (no_texture(m));
	set_sp_index(m);
	if (tok[0] != '(' || tok[ft_strlen(tok) - 1] != ')')
	{
		ft_putendl_fd("Missing parentheses", 2);
		return (-1);
	}
	if (!(path = ft_strndup(&tok[1], ft_strlen(&tok[1]) - 1)))
		return (-1);
	if (load_texture(&env->mlx, path, &sprite, true))
		return (-1);
	free(path);
	if ((!map->txts.byte_size && init_dynarray(&map->txts, sizeof(t_sprite), 0))
		|| push_dynarray(&map->txts, &sprite, false))
		return (-1);
	attribute_texture_index(map, m);
	return (0);
}
