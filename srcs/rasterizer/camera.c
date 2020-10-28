/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:26:22 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 21:50:39 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				allocate_clipping_arrays(t_dynarray arrays[4])
{
	unsigned int	i;

	i = 0;
	while (i < 4)
	{
		if (init_dynarray(&arrays[i], sizeof(t_triangle), MIN_TO_CLIP))
			return (-1);
		i++;
	}
	return (0);
}

void			map_spawn(t_cam *cam, t_map *map, bool respawn)
{
	static t_map	*address = NULL;

	if (address != map && !map->init)
	{
		map->init = true;
		cam->stats.pos = map->spawn;
		cam->stats.pos = vec_add(map->spawn,
			(t_vec3d){0, map->cam.corp.dims.y, 0, 0});
		map->cam.corp.pos = map->spawn;
		map->cam.corp.o = vec_sub(map->cam.corp.pos,
			vec_fdiv(map->cam.corp.dims, 2.0f));
		cam->stats.yaw = map->cam_dir.u;
		cam->stats.pitch = map->cam_dir.v;
	}
	else if (address != map)
	{
		cam->stats.pos = respawn ? map->spawn : map->cam.corp.pos;
		map->cam.corp.pos = respawn ? map->spawn : map->cam.corp.pos;
		map->cam.corp.o = vec_sub(map->cam.corp.pos,
			vec_fdiv(map->cam.corp.dims, 2.0f));
		cam->stats.yaw = respawn ? map->cam.yaw : cam->stats.yaw;
		cam->stats.pitch = respawn ? map->cam.pitch : cam->stats.pitch;
	}
	address = map;
}

static int		init_cameras_meshs(t_env *env)
{
	t_mesh		*cam;
	int			i;

	i = 0;
	while (i < SCENE_MAX)
	{
		cam = &env->maps[i].cam;
		init_cameras_mesh(&env->maps[i], cam);
		i++;
	}
	return (0);
}

int				init_cameras_mesh(t_map *map, t_mesh *cam)
{
	cam->yaw = map->cam_dir.u;
	cam->pitch = map->cam_dir.v;
	cam->corp.pos = map->spawn;
	cam->corp.dims = (t_vec3d){1, 6.5, 1, 1.0f};
	cam->corp.o = vec_sub(cam->corp.pos, vec_fdiv(cam->corp.dims, 2.0f));
	return (0);
}

int				init_camera(t_env *env, t_cam *cam)
{
	cam->stats.aspect_ratio = (float)HGT / (float)WDT;
	cam->stats.fnear = 0.01f;
	cam->stats.ffar = 1000.0f;
	cam->stats.fovd = 80.0f;
	cam->stats.fovr = 1.0f / tan(cam->stats.fovd * 0.5f / 180.0f * 3.14159f);
	cam->stats.fdelta = cam->stats.ffar - cam->stats.fnear;
	cam->stats.pos = (t_vec3d){0, 0, 0, 0};
	cam->stats.dir = (t_vec3d){10.0f, 40.0f, 0.0f, 0.0f};
	cam->stats.pitch = 0;
	cam->stats.yaw = 0;
	cam->light = (t_vec3d){1.0f, 2.0f, 1.0f, 0.0f};
	cam->light = vec_normalize(cam->light);
	init_matrices(cam);
	if (init_cameras_meshs(env) || allocate_clipping_arrays(cam->clip_arrs)
		|| init_dynarray(&cam->to_clip, sizeof(t_triangle), MIN_TO_RASTER)
		|| init_dynarray(&cam->to_raster, sizeof(t_triangle), MIN_TO_RASTER)
		|| !(cam->z_buffer = (float*)malloc(sizeof(float) * (HGT * WDT))))
		return (-1);
	return (0);
}
