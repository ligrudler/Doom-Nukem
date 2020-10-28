/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_damages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	check_hps(t_enemy *mob)
{
	if (mob->hp < 1 && !mob->dead)
	{
		mob->dead = true;
		return (1);
	}
	return (0);
}

static int	moon_cheat(t_env *env, int index)
{
	if (env->player.current->shooting > 0 && env->player.hp < 100)
		if (index == env->custom_env.moon->index)
		{
			env->player.hp++;
			return (1);
		}
	return (0);
}

static int	enemies_do_damages(t_env *env, t_enemy *mob)
{
	env->player.hitmarker = HITMARKER_T;
	mob->hp -= env->player.current->damages;
	if (mob->hp < 1)
	{
		mob->dead = true;
		++env->custom_env.game.kill_count;
		if (sound_system(env, SA_DEATHMONSTER,
			sp_fork(env->sound.volume, PITCH, mob->pos)))
			return (-1);
		if (env->custom_env.game.kill_delay == 0)
			env->custom_env.game.kill_delay = KILL_DELAY;
	}
	env->custom_env.game.moula += mob->dead ? KILL_REWARD : HIT_REWARD;
	return (0);
}

int			enemies_damages(t_env *env)
{
	int			i;
	int			index;
	t_enemy		*mob;

	index = env->mid.mesh->index;
	i = -1;
	while (++i < env->custom_env.mobs.nb_cells)
	{
		mob = dyacc(&env->custom_env.mobs, i);
		if (check_hps(mob))
			continue ;
		if (index >= mob->map_start && index < mob->map_end)
		{
			env->player.hover = true;
			if (env->player.current->shot && !mob->dead)
				return (enemies_do_damages(env, mob));
			return (0);
		}
		if (moon_cheat(env, index))
			return (0);
	}
	return (0);
}
