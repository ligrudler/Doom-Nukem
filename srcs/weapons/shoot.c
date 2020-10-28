/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:40:20 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/21 18:54:19 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	stop_n_play(t_env *env, int source)
{
	if (sound_system(env, source, sp_stop())
		|| sound_system(env, source,
		sp_play(env->sound.volume, PITCH,
		vec_add(env->cam.stats.pos, env->cam.stats.acc))))
		return (-1);
	return (0);
}

int			shoot_current_weapon(t_env *env)
{
	t_weapon	*w;
	bool		sbs;
	bool		single;
	bool		full_auto;

	w = env->player.current;
	sbs = w->shoot_mode == SMODE_SBS;
	single = w->shoot_mode == SMODE_SINGLE;
	full_auto = w->shoot_mode == SMODE_FULL_AUTO;
	if (sbs || single || full_auto)
	{
		w->ready = false;
		w->loaded--;
		stop_n_play(env, w->shoot);
	}
	w->shooting = 60.0f / w->cadency;
	w->shot = true;
	return (0);
}

int			reload_current_weapon(t_env *env)
{
	t_weapon	*w;
	int			need;

	w = env->player.current;
	if (w->loaded == 0 && w->ammos >= w->magazine)
	{
		w->loaded += w->magazine;
		w->ammos -= w->magazine;
	}
	else if ((need = w->magazine - w->loaded) <= w->ammos)
	{
		w->loaded += need;
		w->ammos -= need;
	}
	else
	{
		w->loaded += w->ammos;
		w->ammos = 0;
	}
	if (stop_n_play(env, w->reload))
		return (-1);
	w->reloading = RELOAD_TIME;
	w->start = w->w_map->spawn;
	return (0);
}
