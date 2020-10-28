/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool
	handle_texture(t_map *map, t_sprite *sprite, t_triangle *new)
{
	int			i;

	i = -1;
	if (!map->txts.byte_size)
		return (false);
	while (++i < map->txts.nb_cells)
		if (!ft_memcmp(sprite, dyacc(&map->txts, i), sizeof(t_sprite)))
		{
			new->sp = i;
			return (true);
		}
	return (false);
}

int
	copy_triangles(t_map *map, t_map *mob, t_mesh *m, t_mesh *new)
{
	t_sprite	*sprite;
	t_triangle	t;
	int			i;

	i = 0;
	if (!map->txts.byte_size && init_dynarray(&map->txts, sizeof(t_sprite), 0))
		return (-1);
	while (i < m->tris.nb_cells)
	{
		ft_memcpy(&t, dyacc(&m->tris, i), sizeof(t_triangle));
		t.voxel = false;
		if (t.textured && !handle_texture(map, dyacc(&mob->txts, t.sp), &t))
		{
			sprite = dyacc(&mob->txts, t.sp);
			if (push_dynarray(&map->txts, sprite, false))
				return (-1);
			t.sp = map->txts.nb_cells - 1;
		}
		if (push_dynarray(&new->tris, &t, false))
			return (-1);
		i++;
	}
	return (0);
}

float
	xz_angle(t_vec3d a, t_vec3d b)
{
	float	cross;
	float	dot;

	cross = a.x * b.z - a.z * b.x;
	dot = a.x * b.x + a.z * b.z;
	return (atan2(cross, dot));
}

int
	nodes_3d_1d(t_vec3d dim, t_vec3d pos)
{
	return ((pos.z * dim.x * dim.y) + (pos.y * dim.x) + pos.x);
}

void
	assign_meshs(t_mesh *m)
{
	t_triangle	*t;
	int			i;

	if (!m)
		return ;
	i = 0;
	while (i < m->tris.nb_cells)
	{
		t = dyacc(&m->tris, i);
		t->mesh = m;
		i++;
	}
}
