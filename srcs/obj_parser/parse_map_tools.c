/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:46:31 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 21:46:47 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		attribute_color(t_map *map, t_triangle *new, t_face *f)
{
	new->textured = false;
	if (map->mtls.nb_cells > 0)
		new->color = f->color;
	else
		new->color = 0xffffff;
}

int				get_faces(t_triangle *new, t_map *map, t_face *f, t_mesh *m)
{
	t_vec2d	*t;

	ft_memcpy(&new->points[0], dyacc(&map->pool, f->x - 1), sizeof(t_vec3d));
	ft_memcpy(&new->points[1], dyacc(&map->pool, f->y - 1), sizeof(t_vec3d));
	ft_memcpy(&new->points[2], dyacc(&map->pool, f->z - 1), sizeof(t_vec3d));
	new->points[0].w = 1.0f;
	new->points[1].w = 1.0f;
	new->points[2].w = 1.0f;
	if (f->textured)
	{
		t = dyacc(&map->txt_pool, f->tx - 1);
		ft_memcpy(&new->txt[0], t, sizeof(t_vec2d));
		new->txt[0].w = 1.0f;
		t = dyacc(&map->txt_pool, f->ty - 1);
		ft_memcpy(&new->txt[1], t, sizeof(t_vec2d));
		new->txt[1].w = 1.0f;
		t = dyacc(&map->txt_pool, f->tz - 1);
		ft_memcpy(&new->txt[2], t, sizeof(t_vec2d));
		new->txt[2].w = 1.0f;
		new->mesh = m;
		new->textured = true;
	}
	else
		attribute_color(map, new, f);
	return (0);
}

int				get_line_type(char *c, t_parser *p, char s[PS_MAX][PS_MAX])
{
	static char		*qualis[PS_MAX] = {"o", "v", "vt", "s", "f", "#", "mtllib",
									"usemtl"};
	unsigned int	i;

	i = 0;
	while (i < PS_MAX)
	{
		if (ft_strlen(c) == ft_strlen(qualis[i])
			&& !ft_strcmp(c, qualis[i]))
		{
			p->tstate = (char)i;
			if (!s[(int)p->state][(int)p->tstate])
				return (-1);
			p->state = p->tstate;
			return (0);
		}
		i++;
	}
	return (1);
}
