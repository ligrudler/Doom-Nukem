/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loots_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:57:23 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 14:57:24 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		loot_nuke(t_env *env)
{
	t_enemy	*mob;
	int		i;

	i = 0;
	while (i < env->custom_env.mobs.nb_cells)
	{
		mob = dyacc(&env->custom_env.mobs, i);
		mob->hp = 0;
		mob->dead = true;
		i++;
	}
	if (sound_system(env, SA_LNUKE,
		sp_play(env->sound.volume, PITCH, env->cam.stats.pos)))
		return (-1);
	return (0);
}

int		loot_money(t_env *env)
{
	int		bonus;
	int		cumul;

	cumul = env->custom_env.game.wave * 42;
	bonus = (rand() % (MAX_CASH + cumul)) + MIN_CASH;
	env->custom_env.game.moula += bonus;
	while (env->custom_env.game.moula % 10)
		env->custom_env.game.moula++;
	if (sound_system(env, SA_LCASH,
		sp_play(env->sound.volume, PITCH, env->cam.stats.pos)))
		return (-1);
	return (0);
}

int		loot_shield(t_env *env)
{
	env->player.god = GOD_TIME;
	if (sound_system(env, SA_LGODSTART,
		sp_play(env->sound.volume, PITCH, env->cam.stats.pos)))
		return (-1);
	return (0);
}

int		loot_ammos(t_env *env)
{
	t_weapon	*w;
	int			i;

	i = 0;
	while (i < env->player.weapons.nb_cells)
	{
		w = dyacc(&env->player.weapons, i);
		w->ammos = w->max_ammos;
		i++;
	}
	if (sound_system(env, SA_LAMMOS,
		sp_play(env->sound.volume, PITCH, env->cam.stats.pos)))
		return (-1);
	return (0);
}
