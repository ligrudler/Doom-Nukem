/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bounding_boxs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:10:44 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/18 20:10:46 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	cmp_xyz(t_vec3d pos, t_vec3d p, t_vec3d *min, t_vec3d *max)
{
	if (p.x - pos.x < min->x)
		min->x = p.x - pos.x;
	else if (p.x - pos.x > max->x)
		max->x = p.x - pos.x;
	if (p.y - pos.y < min->y)
		min->y = p.y - pos.y;
	else if (p.y - pos.y > max->y)
		max->y = p.y - pos.y;
	if (p.z - pos.z < min->z)
		min->z = p.z - pos.z;
	else if (p.z - pos.z > max->z)
		max->z = p.z - pos.z;
}

static int	get_box_dims(t_mesh *m)
{
	t_triangle	*t;
	t_vec3d		min;
	t_vec3d		max;
	int			i;
	int			j;

	i = 0;
	min = (t_vec3d){INFINITY, INFINITY, INFINITY, INFINITY};
	max = (t_vec3d){-INFINITY, -INFINITY, -INFINITY, -INFINITY};
	while (i < m->tris.nb_cells)
	{
		j = 0;
		if (!(t = dyacc(&m->tris, i)))
			return (-1);
		while (j < 3)
		{
			cmp_xyz(m->corp.pos, t->points[j], &min, &max);
			j++;
		}
		i++;
	}
	m->corp.dims = vec_sub(max, min);
	return (0);
}

int			init_bounding_box(t_mesh *m)
{
	if (get_box_dims(m))
		return (-1);
	m->corp.o = vec_sub(m->corp.pos, vec_fdiv(m->corp.dims, 2.0f));
	return (0);
}
