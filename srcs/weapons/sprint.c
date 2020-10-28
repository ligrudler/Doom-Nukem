/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:46:53 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 03:00:01 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	do_sprint(t_env *env)
{
	bool	ret;

	ret = true;
	if (env->player.current->reloading > 0
		|| env->player.current->shooting > 0)
		ret = false;
	if (env->edit_env.map.cam.corp.v.x == 0
		&& env->edit_env.map.cam.corp.v.y == 0
		&& env->edit_env.map.cam.corp.v.z == 0)
		ret = false;
	if (ret == false)
		sound_system(env, SA_STEP, sp_stop());
	return (ret);
}

static bool	move_keys(t_env *env)
{
	return ((env->events.keys[KEY_W]
		|| env->events.keys[KEY_A]
		|| env->events.keys[KEY_S]
		|| env->events.keys[KEY_D]));
}

static int	step_sound(t_env *env)
{
	static int	delay = 0;
	t_vec3d		pos;

	if (delay-- == 0)
	{
		pos = env->cam.stats.pos;
		pos.y -= 2;
		if (move_keys(env) && sound_system(env, SA_STEP,
			sp_play(env->sound.volume / 1.8f, PITCH, pos)))
			return (-1);
		delay = env->events.keys[KEY_SHIFT_LEFT] ? 4 : 8;
	}
	if (env->events.keys[KEY_SPACE] && sound_system(env, SA_STEP, sp_stop()))
		return (-1);
	return (0);
}

static void	movements(t_env *env, float speeds[2], int *frame)
{
	if (env->events.keys[KEY_SPACE])
		return ;
	if (*frame > 0)
	{
		env->player.current->w_map->spawn.y -= speeds[0];
		(*frame)--;
	}
	else if (*frame > -speeds[1])
	{
		env->player.current->w_map->spawn.y += speeds[0];
		(*frame)--;
	}
	if (*frame == -speeds[1])
		*frame = speeds[1];
}

int			handle_sprint(t_env *env)
{
	static t_vec3d	reset;
	static int		frame = 0;
	static bool		on = false;
	static bool		first = true;
	float			speeds[2];

	if (env->phy_env.type_move == false || !do_sprint(env))
		return (0);
	if (step_sound(env))
		return (-1);
	speeds[0] = env->events.keys[KEY_SHIFT_LEFT] ? 0.002f : 0.001f;
	speeds[1] = env->events.keys[KEY_SHIFT_LEFT] ? W_SHAKE / 2 : W_SHAKE;
	if (first && !(first = false))
		reset = env->player.current->w_map->spawn;
	on = (!on && move_keys(env));
	on ? movements(env, speeds, &frame) : 0;
	if (on && !move_keys(env))
	{
		on = false;
		frame = env->events.keys[KEY_SHIFT_LEFT] ? -speeds[1] : speeds[1];
		env->player.current->w_map->spawn = reset;
		return (sound_system(env, SA_STEP, sp_stop()));
	}
	return (0);
}
