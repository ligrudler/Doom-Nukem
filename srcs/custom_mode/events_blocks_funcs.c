/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_blocks_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:44:01 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 19:01:51 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		jukeboxs_play_sound(t_env *env)
{
	t_events	*e;
	static int	ambient = 2;
	static int	delay = 0;

	e = &env->events;
	if (e->keys[KEY_F] && env->custom_env.game.moula >= 500 && delay == 0)
	{
		delay = 40;
		if (ambient < SA_GAME1 || ambient > SA_MAPED)
			ambient = SA_GAME1;
		if (sound_system(env, ambient, sp_overall(0, SA_MAPED,
			sp_play(env->sound.volume, PITCH, env->cam.stats.pos))))
			return (-1);
		env->custom_env.game.moula -= 500;
	}
	else if ((e->keys[KEY_LEFT] || e->keys[KEY_RIGHT]) && delay == 0)
	{
		delay = 5;
		ambient = e->keys[KEY_LEFT] ? ambient - 1 : ambient + 1;
		ambient = ambient < SA_GAME1 ? SA_MAPED : ambient;
		ambient = ambient > SA_MAPED ? SA_GAME1 : ambient;
	}
	delay = delay > 0 ? delay - 1 : delay;
	return (ambient);
}

int				handle_jukeboxs(t_env *env, t_event_block *block)
{
	char	*current;

	if (block->id != BE_JUKEBOX)
		return (0);
	if (vec3d_dist(env->cam.stats.pos, get_block_center(block)) < EVENT_DIST)
	{
		textual_hint(env, "F", "PLAY ( 500)", 0);
		textual_hint(env, "{", "PREVIOUS", 1);
		textual_hint(env, "}", "NEXT", 2);
		if (!(current = ft_itoa(jukeboxs_play_sound(env) - 2)))
			return (-1);
		textual_hint(env, current, "current track", 3);
		ft_strdel(&current);
		return (1);
	}
	return (0);
}

int				handle_mystery_boxs(t_env *env, t_event_block *block)
{
	static bool	button = false;
	bool		full;

	if (block->id != BE_CHEST)
		return (0);
	if (vec3d_dist(env->cam.stats.pos, get_block_center(block)) < EVENT_DIST)
	{
		full = (env->player.weapons.nb_cells == W_MAX);
		textual_hint(env, "F", full ? "fuck off, you full equiped bastard"
			: "GET RANDOM WEAPON ( 1000)", 0);
		if (!full && env->events.keys[KEY_F]
			&& env->custom_env.game.moula >= 1000 && button)
		{
			button = false;
			env->custom_env.game.moula -= 1000;
			if (add_random_weapon(env))
				return (-1);
			if (sound_system(env, SA_CHANGE,
				sp_fork(env->sound.volume, PITCH, env->cam.stats.pos)))
				return (-1);
		}
		button = !env->events.keys[KEY_F];
		return (1);
	}
	return (0);
}

int				handle_doors(t_env *env, t_event_block *block)
{
	if (block->id != BE_DOOR)
		return (0);
	if (vec3d_dist(env->cam.stats.pos, get_block_center(block)) < EVENT_DIST)
	{
		textual_hint(env, "F", "open the door ( cost 500)", 0);
		if (env->events.keys[KEY_F] && env->custom_env.game.moula >= 500)
		{
			env->custom_env.game.moula -= 500;
			if (del_door(env, block))
				return (-1);
			if (sound_system(env, SA_DOOR,
				sp_fork(env->sound.volume, PITCH, env->cam.stats.pos)))
				return (-1);
		}
		return (1);
	}
	return (0);
}

int				handle_lavas(t_env *env, t_event_block *block)
{
	int				ret;
	float			dst;
	t_vec3d			center;
	static int		delay = LAVA_DELAY;
	static int		delay2 = 10;

	if (!(ret = 0) && block->id != BE_LAVA)
		return (0);
	center = get_block_center(block);
	dst = vec3d_dist(env->cam.stats.pos, center);
	if (lava_sound(env, block))
		return (-1);
	if (dst < EVENT_DIST && (ret = 1))
		if (--delay == 0)
		{
			if (delay2++ == 10
				&& !(delay2 = 0))
				if (sound_system(env, SA_PLAYER_DAMAGE,
					sp_fork(env->sound.volume, PITCH, env->cam.stats.pos)))
					return (-1);
			env->player.hp--;
			delay = LAVA_DELAY;
		}
	return (ret);
}
