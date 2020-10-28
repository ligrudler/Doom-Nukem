/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:11:53 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/18 20:11:55 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	update_speeds_collide_cam(t_env *env, t_mesh *cam, t_map *map)
{
	t_collide			*c;
	int					i;
	int					j;

	i = 0;
	j = 0;
	if (env->cam.stats.onwall == 1 || env->cam.stats.onfloor == 1
		|| env->cam.stats.onroof == 1)
		scan_actuall_collide(env, map);
	while (i < env->phy_env.collides_cam.nb_cells)
	{
		c = dyacc(&env->phy_env.collides_cam, i);
		type_of_plan(env, c, map);
		i++;
	}
	if ((env->cam.stats.onfloor == 0) || (i == 0))
	{
		env->cam.stats.onfloor = 0;
		phy_gravitax_cam(env, cam);
	}
}

void	update_positions_cam(t_env *env, t_map *map, t_mesh *cam)
{
	if (env->cam.stats.onfloor == 1)
		cam->corp.v = vec_add(cam->corp.v,
				vec_fmult((t_vec3d){0, env->phy_env.crch_v, 0, 0}, 0.1));
	translate_mesh(map, cam, cam->corp.v);
	env->cam.stats.pos = vec_add(env->cam.stats.pos, cam->corp.v);
	cam->corp.o = vec_sub(env->cam.stats.pos, vec_fdiv(cam->corp.dims,
	1.0f * env->cam.stats.crouch));
}
