/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:30:19 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 19:42:01 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*rasthreader(void *param)
{
	t_rasthread	*thr;
	t_env		*env;
	t_triangle	*t;

	thr = (t_rasthread*)param;
	env = thr->env;
	while (thr->index < thr->end)
	{
		t = dyacc(&env->cam.to_raster, thr->index);
		fill_triangle_texture((t_env*)thr->env, t);
		if (env->data.wireframe)
			draw_triangle(&env->mlx, *t);
		thr->index++;
	}
	if (thr->mono)
		return (NULL);
	else
		pthread_exit(NULL);
}

void	monothread_raster(void *e)
{
	t_rasthread		thread;
	t_env			*env;

	env = e;
	thread.env = env;
	thread.tris = &env->cam.to_raster;
	thread.start = 0;
	thread.index = 0;
	thread.end = env->cam.to_raster.nb_cells;
	thread.mono = true;
	rasthreader(&thread);
}

int		raster_weapon(t_env *env, t_map *map)
{
	t_cam	cam;

	ft_memcpy(&cam, &env->cam, sizeof(t_cam));
	if (rasterizer(env, map, true))
		return (-1);
	ft_memcpy(&env->cam, &cam, sizeof(t_cam));
	return (0);
}

int		rasterizer(t_env *e, t_map *map, bool respawn)
{
	t_mesh		*m;
	int			i;
	int			j;

	i = -1;
	map_spawn(&e->cam, map, respawn);
	compute_view_matrice(e);
	while (++i < map->nmesh)
	{
		while ((m = dyacc(&map->meshs, i))
			&& i < map->nmesh && m->type == BTXT_NONE)
			i++;
		if (m == NULL)
			return (0);
		compute_rotation_matrices(e);
		j = -1;
		while (++j < m->tris.nb_cells)
			if (triangle_pipeline(e, dyacc(&m->tris, j), &e->cam.to_clip, m))
				return (-1);
	}
	if (raster_triangles(e, &e->cam.to_clip))
		return (-1);
	e->scene = map->index;
	return (0);
}
