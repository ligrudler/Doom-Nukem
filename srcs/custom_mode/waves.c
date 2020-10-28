/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:19:04 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 15:31:27 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	start_game(t_env *env)
{
	t_custom_game	*game;

	env->player.hp = START_HP;
	game = &env->custom_env.game;
	game->wave = 1;
	env->hud.timewave = env->data.time.tv_sec;
	game->mobs_pv = MOB_START_HP;
	game->mobs_speed = MOB_START_SPEED;
	game->lmob = MOB_LSTART;
	game->current_lmob = MOB_LSTART;
	game->moula = START_MOULA;
	game->spawn_speed = RESPAWN_DELAY;
}

static bool	next_wave(t_env *env)
{
	static bool		first = true;

	if (first)
		env->custom_env.game.countdown = INTER_WAVE;
	first = false;
	env->custom_env.game.countdown -= env->data.spent;
	if (env->custom_env.game.countdown < 0)
	{
		env->custom_env.game.countdown = INTER_WAVE;
		return (true);
	}
	return (false);
}

char		enemy_wave(t_env *env)
{
	char	type;

	if (env->custom_env.game.wave % 5 == 0)
		return (ENEMY_MAGE);
	else
	{
		type = ENEMY_MAGE;
		while (type == ENEMY_MAGE)
			type = rand() % ENEMY_MAX;
		return (type);
	}
}

void		handle_waves(t_env *env)
{
	t_custom_game	*game;

	game = &env->custom_env.game;
	if (game->wave == 0)
	{
		start_game(env);
		return ;
	}
	if (game->current_lmob == 0 && env->custom_env.mobs.nb_cells == 0)
		if (next_wave(env))
		{
			game->wave++;
			env->hud.timewave = env->data.time.tv_sec;
			game->mobs_pv *= MOB_PV_COEFF;
			game->lmob += MOB_NB_ADD;
			game->current_lmob = game->lmob;
			game->spawn_speed -= SPAWN_SPEED_SUB;
		}
}
