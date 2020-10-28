/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_rotations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			enemies_rotate_mob(t_enemy *mob, float fcos, float fsin,
		void (*rotation)(t_vec3d *v, t_vec3d m, float fcos, float fsin))
{
	int			i;
	int			j;
	t_mesh		*mesh;
	t_triangle	*tri;

	rotation(&mob->head, zero_vector(), fcos, fsin);
	i = mob->map_start - 1;
	while (++i < mob->map_end)
	{
		mesh = dyacc(&mob->map->meshs, i);
		j = -1;
		while (++j < mesh->tris.nb_cells)
		{
			tri = dyacc(&mesh->tris, j);
			rotation(&tri->points[0], mob->pos, fcos, fsin);
			rotation(&tri->points[1], mob->pos, fcos, fsin);
			rotation(&tri->points[2], mob->pos, fcos, fsin);
		}
	}
}

void			enemies_last_rotation(t_enemy *mob, t_vec3d cam)
{
	float	fcos;
	float	fsin;
	t_vec3d	goal;

	goal = vec_sub(cam, mob->pos);
	mob->yaw = xz_angle(mob->head, goal) * mob->speed;
	fcos = cos(mob->yaw);
	fsin = sin(mob->yaw);
	enemies_rotate_mob(mob, fcos, fsin, rotate_y);
}
