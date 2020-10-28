/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:10:21 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/18 20:17:23 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		physic_engine(t_env *env, t_map *maps)
{
	t_events	*e;
	t_mesh		*cam;

	cam = &maps->cam;
	e = &env->events;
	if (report_cam_collisions(env, maps))
		return (-1);
	update_speeds_collide_cam(env, cam, maps);
	update_positions_cam(env, maps, cam);
	stop_position_cam(env, maps, cam);
	clear_dynarray(&env->phy_env.collides_cam);
	env->custom_env.game.moula < 0 ? env->custom_env.game.moula = 0 : 0;
	return (0);
}
