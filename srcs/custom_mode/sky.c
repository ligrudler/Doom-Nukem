/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:18:14 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 15:18:15 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		tweek_stars_height(t_env *env, t_vec3d star, float *y)
{
	float		x;
	float		z;
	t_vec3d		middle;
	t_ed_map	*map;

	map = &env->edit_env.new_map;
	middle = (t_vec3d){ map->width, map->height, map->depth, 0 };
	x = star.x - middle.x;
	z = star.z - middle.z;
	*y -= 1 / rsqrt(x * x + z * z) / 2;
}

static int		spawn_stars(t_env *env, t_vec3d o, t_vec3d box)
{
	t_vec3d		spawn;

	spawn.x = (rand() % (int)box.x) - o.x;
	spawn.y = (rand() % (int)box.y) - o.y;
	spawn.z = (rand() % (int)box.z) - o.z;
	tweek_stars_height(env, spawn, &spawn.y);
	return (!copy_to_scene(&env->edit_env.map, &env->maps[SCENE_STAR], spawn));
}

static int		spawn_moon(t_env *env, t_vec3d o)
{
	t_vec3d	pos[4];
	t_mesh	*m;
	int		p;

	if (o.x > STARS_SPREAD * STARS_SPREAD)
		o.x = STARS_SPREAD * STARS_SPREAD;
	if (o.y < STARS_SPREAD * -10)
		o.y = STARS_SPREAD * -10;
	if (o.z > STARS_SPREAD * STARS_SPREAD)
		o.z = STARS_SPREAD * STARS_SPREAD;
	pos[0] = (t_vec3d){-o.x / MOON_SCALE, -o.y, -o.z / MOON_SCALE, 0};
	pos[1] = (t_vec3d){-o.x / MOON_SCALE, -o.y, o.z / MOON_SCALE, 0};
	pos[2] = (t_vec3d){o.x / MOON_SCALE, -o.y, -o.z / MOON_SCALE, 0};
	pos[3] = (t_vec3d){o.x / MOON_SCALE, -o.y, o.z / MOON_SCALE, 0};
	p = rand() % 4;
	m = copy_to_scene(&env->edit_env.map, &env->maps[SCENE_MOON], pos[p]);
	env->custom_env.moon = m;
	return (m ? 0 : -1);
}

int				init_sky(t_env *env)
{
	int			i;
	int			stars_scale;
	t_vec3d		box;
	t_vec3d		o;
	t_ed_map	*map;

	map = &env->edit_env.new_map;
	stars_scale = map->width > map->depth ? map->width : map->depth;
	stars_scale = stars_scale < STARS_SPREAD ?
		STARS_SPREAD : stars_scale;
	o = (t_vec3d){ stars_scale * STARS_SPREAD,
					-stars_scale * STARS_MIN_HEIGHT,
					stars_scale * STARS_SPREAD, 0 };
	box = (t_vec3d){ stars_scale * 2 + o.x * 2,
					-stars_scale * STARS_MAX_HEIGHT,
					stars_scale * 2 + o.z * 2, 0 };
	i = -1;
	while (++i < NB_STARS)
		if (spawn_stars(env, o, box))
			return (-1);
	return (spawn_moon(env, o));
}
