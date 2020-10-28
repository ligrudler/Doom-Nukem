/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:21:53 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/12 21:24:47 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		left_quarters(t_env *env, int x, int y)
{
	float	ratio;
	int		hwdt;
	int		hhgt;

	ratio = env->cam.stats.aspect_ratio;
	hwdt = env->data.half_wdt;
	hhgt = env->data.half_hgt;
	if (x <= hwdt && y < hhgt)
	{
		env->cam.stats.yaw -= fabs((hwdt - x) * SENSI) * ratio;
		if (env->cam.stats.pitch + fabs((hhgt - y) * SENSI) <= 90)
			env->cam.stats.pitch += fabs((hhgt - y) * SENSI);
		return (1);
	}
	else if (x < hwdt && y >= hhgt)
	{
		env->cam.stats.yaw -= fabs((hwdt - x) * SENSI) * ratio;
		if (env->cam.stats.pitch - fabs((hhgt - y) * SENSI) >= -90)
			env->cam.stats.pitch -= fabs((hhgt - y) * SENSI);
		return (1);
	}
	return (0);
}

static int		right_quarters(t_env *env, int x, int y)
{
	float	ratio;
	int		hwdt;
	int		hhgt;

	ratio = env->cam.stats.aspect_ratio;
	hwdt = env->data.half_wdt;
	hhgt = env->data.half_hgt;
	if (x >= hwdt && y < hhgt)
	{
		env->cam.stats.yaw += fabs((hwdt - x) * SENSI) * ratio;
		if (env->cam.stats.pitch + fabs((hhgt - y) * SENSI) <= 90)
			env->cam.stats.pitch += fabs((hhgt - y) * SENSI);
		return (1);
	}
	else if (x > hwdt && y >= hhgt)
	{
		env->cam.stats.yaw += fabs((hwdt - x) * SENSI) * ratio;
		if (env->cam.stats.pitch - fabs((hhgt - y) * SENSI) >= -90)
			env->cam.stats.pitch -= fabs((hhgt - y) * SENSI);
		return (1);
	}
	return (0);
}

void			camera_aim(t_env *env)
{
	t_data		*data;
	int			mouse_x;
	int			mouse_y;

	data = &env->data;
	mouse_x = env->events.mouse_pos.x;
	mouse_y = env->events.mouse_pos.y;
	if (!left_quarters(env, mouse_x, mouse_y))
		right_quarters(env, mouse_x, mouse_y);
	mlx_mouse_move(env->mlx.mlx_win, data->half_wdt, data->half_hgt);
	env->events.mouse_pos.x = data->half_wdt;
	env->events.mouse_pos.y = data->half_hgt;
}
