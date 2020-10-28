/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:13:47 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 14:09:10 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	wound(t_env *env, t_enemy *mob)
{
	static float	sndelay = 1.0f;

	env->player.hp -= mob->damages;
	if (sndelay >= 1.0f)
	{
		if (sound_system(env, SA_PLAYER_DAMAGE,
			sp_fork(env->sound.volume, 1, env->cam.stats.pos)))
			return (-1);
		sndelay = 1.0f;
	}
	else
		sndelay -= env->data.spent;
	return (0);
}

static int	check_wounds(t_env *env)
{
	t_enemy			*mob;
	int				i;

	i = 0;
	while (i < env->custom_env.mobs.nb_cells)
	{
		mob = dyacc(&env->custom_env.mobs, i);
		if (vec3d_dist(env->cam.stats.pos, mob->pos) < EVENT_DIST)
		{
			mob->peace--;
			if (mob->peace <= 0)
			{
				mob->peace = MOB_PEACE_TIME;
				if (wound(env, mob))
					return (-1);
			}
		}
		i++;
	}
	return (0);
}

static int	godmode(t_env *env)
{
	static bool	end = true;
	int			fade;

	fade = 10;
	if (env->player.hp < 142 && env->player.god > (GOD_TIME / fade))
		env->player.hp++;
	if (env->player.hp > 100 && env->player.god < (GOD_TIME / fade))
	{
		if (end && sound_system(env, SA_LGODEND,
			sp_play(env->sound.volume, PITCH, env->cam.stats.pos)))
			return (-1);
		end = true;
		env->player.hp--;
	}
	env->player.god -= env->data.spent;
	if (env->player.god <= 0.0f)
		end = true;
	return (0);
}

int			handle_player(t_env *env)
{
	static int	heal = HEAL_SPEED;
	int			i;

	i = 0;
	heal--;
	if (env->player.god > 0.0f)
		return (godmode(env));
	if (env->player.hp < 1 && switch_custom_context(env, CUSTOM_SC_GAME_OVER))
		return (-1);
	if (heal <= 0)
	{
		if (env->player.hp < START_HP)
			env->player.hp++;
		heal = HEAL_SPEED;
	}
	if (env->custom_env.spawn_jump > 0)
	{
		env->events.keys[KEY_SPACE] = true;
		env->custom_env.spawn_jump--;
	}
	else if (env->custom_env.spawn_jump == 0 && --env->custom_env.spawn_jump)
		env->events.keys[KEY_SPACE] = false;
	return (check_wounds(env));
}
