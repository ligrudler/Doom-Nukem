/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:10:55 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/21 22:51:22 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		set_mesh_position(t_mesh *m)
{
	t_vec3d		average;
	t_triangle	*t;
	int			i;

	i = 0;
	average = (t_vec3d){0, 0, 0, 0};
	while (i < m->tris.nb_cells)
	{
		if (!(t = dyacc(&m->tris, i)))
			return (-1);
		average = vec_add(average, t->points[0]);
		average = vec_add(average, t->points[1]);
		average = vec_add(average, t->points[2]);
		i++;
	}
	m->corp.pos = vec_fdiv(average, (float)i);
	m->corp.pos = vec_fdiv(m->corp.pos, 3.0f);
	return (0);
}

int				init_map_physics(t_map *map)
{
	t_mesh	*m;
	int		i;

	i = 0;
	while (i < map->nmesh)
	{
		if (!(m = dyacc(&map->meshs, i))
			|| set_mesh_position(m)
			|| init_bounding_box(m))
			return (-1);
		i++;
	}
	return (0);
}

int				init_physic_engine(t_env *env)
{
	int			i;

	i = 0;
	while (i < SCENE_MAX)
	{
		if (init_map_physics(&env->maps[i]))
			return (-1);
		ft_putchar(i == SCENE_MAX - 1 ? '\0' : '\r');
		i++;
	}
	ft_memset((void*)&env->phy_env, 0, sizeof(t_physics));
	env->phy_env.gravity = 0.0000981;
	env->phy_env.type_move = true;
	return (0);
}
