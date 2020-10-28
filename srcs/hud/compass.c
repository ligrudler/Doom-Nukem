/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 08:22:11 by grudler           #+#    #+#             */
/*   Updated: 2020/07/18 17:18:36 by grudler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		draw_events_indicator(t_env *env)
{
	int				i;
	t_event_block	*event;
	float			angle;
	int				offsetx;
	float			dist;

	i = -1;
	while (++i < env->custom_env.events.nb_cells)
	{
		event = dyacc(&env->custom_env.events, i);
		if (event->id == BE_CHEST)
		{
			angle = xz_angle(env->cam.stats.dir,
				vec_sub(get_block_center(event),
				env->cam.stats.pos)) * (180 / M_PI);
			offsetx = WDT * (angle + 180) / 360;
			dist = vec3d_dist(get_block_center(event), env->cam.stats.pos) / 2;
			if (offsetx > env->data.third_wdt
				&& offsetx + EN_WDT < env->data.third_wdt * 2)
				draw_rectangle(env->mlx.img_data, (t_point){offsetx,
					COMP_HGT + (dist / 2)},
					(t_point){EN_WDT, COMP_HGT - dist}, 0x00FFFF);
		}
	}
}

static void		draw_ennemies_indicator(t_env *env)
{
	int			i;
	t_enemy		*mob;
	float		angle;
	int			offsetx;
	float		dist;

	i = -1;
	while (++i < env->custom_env.mobs.nb_cells)
	{
		mob = dyacc(&env->custom_env.mobs, i);
		angle = xz_angle(env->cam.stats.dir,
			vec_sub(mob->pos, env->cam.stats.pos)) * (180 / M_PI);
		offsetx = WDT * (angle + 180) / 360;
		dist = vec3d_dist(mob->pos, env->cam.stats.pos) / 2;
		if (offsetx > env->data.third_wdt
			&& offsetx + EN_WDT < env->data.third_wdt * 2)
			draw_rectangle(env->mlx.img_data,
				(t_point){offsetx, COMP_HGT + (dist / 2)},
				(t_point){EN_WDT, COMP_HGT - dist}, NORMAL_RED);
	}
}

static void		print_cord(t_env *env, float index, t_point points, bool east)
{
	t_ttf_config	*conf;
	char			*cord;

	conf = ttf_config();
	conf->size = 20;
	if (index == 0)
		cord = "S";
	else if (index == 180)
		cord = "N";
	else if (index == 90)
		cord = (east ? "E" : "W");
	else
		cord = "I";
	ft_strcpy((char *)conf->s, cord);
	my_string_put(env, env->mlx.img_data, points, FONT_COOLVETICA);
}

static void		draw_coordinates(t_env *env)
{
	t_vec3d		nord;
	float		angle;
	float		index;
	int			offsetx_right;
	int			offsetx_left;

	nord = (t_vec3d){1, 0, 0, 0};
	angle = xz_angle(env->cam.stats.dir, nord) * 180 / M_PI;
	index = 0;
	while (index <= 360)
	{
		angle = angle < 0 ? 180 + (180 + angle) : angle;
		offsetx_right = ((angle - index) / 360) * WDT;
		offsetx_left = ((angle + index) / 360) * WDT;
		if (offsetx_right > env->data.third_wdt &&
			offsetx_right + 10 < env->data.third_wdt * 2)
			print_cord(env, index, (t_point){offsetx_right, OFF_CORD}, true);
		if (offsetx_left > env->data.third_wdt &&
			offsetx_left + 10 < env->data.third_wdt * 2)
			print_cord(env, index, (t_point){offsetx_left, OFF_CORD}, false);
		index += 10;
	}
}

void			draw_compass(t_env *env)
{
	draw_rectangle(env->mlx.img_data, (t_point){env->data.third_wdt, COMP_HGT},
		(t_point){env->data.third_wdt, COMP_HGT}, DARK_GREY);
	draw_rectangle(env->mlx.img_data,
		(t_point){env->data.half_wdt - IND_WDT / 2, COMP_HGT},
		(t_point){IND_WDT, COMP_HGT}, LIGHT_GREY);
	draw_ennemies_indicator(env);
	draw_events_indicator(env);
	draw_coordinates(env);
}
