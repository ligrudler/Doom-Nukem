/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:33:05 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:38:38 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	cmp_menu_to_intro(t_env *env)
{
	*snow_play() = true;
	if (sound_system(env, 0, sp_overall(0, SA_MAX, sp_stop())))
		exit_doom(env, "error sound_system", 0, -1);
	if (sound_system(env, SA_BUTTON, sp_play(1, PITCH, env->cam.stats.pos)))
		exit_doom(env, "error sound_system", 0, -1);
	mlx_mouse_hide();
}

void	cmp_intro_to_game(t_env *env)
{
	static bool	first = true;

	if (first)
	{
		rasterizer(env, &env->maps[SCENE_START_ROOM], true);
		rasterizer(env, &env->maps[SCENE_DUST], true);
		first = false;
	}
	env->cmp_env.countdown = COUNTDOWN;
	env->cmp_env.sector = SECTOR_START_ROOM;
	env->cmp_env.done = false;
	env->cmp_env.failed = false;
	mlx_mouse_hide();
}

void	cmp_game_to_end(t_env *env)
{
	int		i;

	i = 0;
	env->cmp_env.end_t = 5;
	env->cmp_env.hint_t = 0;
	while (i < NB_BUZZERS)
	{
		if (env->cmp_env.buzzers[i].on)
			switch_bit(env, &env->cmp_env.buzzers[i], false);
		i++;
	}
}

void	cmp_end_to_menu(t_env *env)
{
	(void)env;
	mlx_mouse_show();
	mlx_mouse_show();
}
