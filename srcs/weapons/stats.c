/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:41:52 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/16 19:11:08 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	damages_n_accuracy(t_env *env)
{
	env->weapons[W_FAMAS].damages = 30;
	env->weapons[W_AK47].damages = 50;
	env->weapons[W_SAWED_OFF].damages = 100;
	env->weapons[W_GLOCK_18].damages = 30;
	env->weapons[W_AUG].damages = 40;
	env->weapons[W_UMP45].damages = 30;
	env->weapons[W_MAG7].damages = 80;
	env->weapons[W_GALIL].damages = 25;
	env->weapons[W_NEGEV].damages = 60;
	env->weapons[W_TEC9].damages = 45;
	env->weapons[W_FAMAS].accuracy = 0.8f;
	env->weapons[W_AK47].accuracy = 0.6f;
	env->weapons[W_SAWED_OFF].accuracy = 0.3f;
	env->weapons[W_GLOCK_18].accuracy = 0.5f;
	env->weapons[W_AUG].accuracy = 0.8f;
	env->weapons[W_UMP45].accuracy = 0.5;
	env->weapons[W_MAG7].accuracy = 0.4;
	env->weapons[W_GALIL].accuracy = 0.6;
	env->weapons[W_NEGEV].accuracy = 0.4;
	env->weapons[W_TEC9].accuracy = 0.8;
}

static void	magazine_n_reticle(t_env *env)
{
	env->weapons[W_FAMAS].magazine = 25;
	env->weapons[W_AK47].magazine = 30;
	env->weapons[W_SAWED_OFF].magazine = 8;
	env->weapons[W_GLOCK_18].magazine = 18;
	env->weapons[W_AUG].magazine = 30;
	env->weapons[W_UMP45].magazine = 32;
	env->weapons[W_MAG7].magazine = 12;
	env->weapons[W_GALIL].magazine = 35;
	env->weapons[W_NEGEV].magazine = 100;
	env->weapons[W_TEC9].magazine = 18;
	env->weapons[W_FAMAS].reticle = 20;
	env->weapons[W_AK47].reticle = 24;
	env->weapons[W_SAWED_OFF].reticle = 32;
	env->weapons[W_GLOCK_18].reticle = 16;
	env->weapons[W_AUG].reticle = 20;
	env->weapons[W_UMP45].reticle = 22;
	env->weapons[W_MAG7].reticle = 30;
	env->weapons[W_GALIL].reticle = 22;
	env->weapons[W_NEGEV].reticle = 30;
	env->weapons[W_TEC9].reticle = 20;
}

static void	cadency_n_shoot_mode(t_env *env)
{
	env->weapons[W_FAMAS].cadency = 1000;
	env->weapons[W_AK47].cadency = 600;
	env->weapons[W_SAWED_OFF].cadency = 200;
	env->weapons[W_GLOCK_18].cadency = 300;
	env->weapons[W_AUG].cadency = 650;
	env->weapons[W_UMP45].cadency = 600;
	env->weapons[W_MAG7].cadency = 250;
	env->weapons[W_GALIL].cadency = 650;
	env->weapons[W_NEGEV].cadency = 850;
	env->weapons[W_TEC9].cadency = 300;
	env->weapons[W_FAMAS].shoot_mode = SMODE_FULL_AUTO;
	env->weapons[W_AK47].shoot_mode = SMODE_FULL_AUTO;
	env->weapons[W_SAWED_OFF].shoot_mode = SMODE_SBS;
	env->weapons[W_GLOCK_18].shoot_mode = SMODE_SINGLE;
	env->weapons[W_AUG].shoot_mode = SMODE_FULL_AUTO;
	env->weapons[W_UMP45].shoot_mode = SMODE_FULL_AUTO;
	env->weapons[W_MAG7].shoot_mode = SMODE_SBS;
	env->weapons[W_GALIL].shoot_mode = SMODE_FULL_AUTO;
	env->weapons[W_NEGEV].shoot_mode = SMODE_FULL_AUTO;
	env->weapons[W_TEC9].shoot_mode = SMODE_SINGLE;
}

static void	recoil_n_max_ammos(t_env *env)
{
	env->weapons[W_FAMAS].recoil = 0.1f;
	env->weapons[W_AK47].recoil = 0.05f;
	env->weapons[W_SAWED_OFF].recoil = 0.3f;
	env->weapons[W_GLOCK_18].recoil = 0.05;
	env->weapons[W_AUG].recoil = 0.1f;
	env->weapons[W_UMP45].recoil = 0.1f;
	env->weapons[W_MAG7].recoil = 0.3f;
	env->weapons[W_GALIL].recoil = 0.1f;
	env->weapons[W_NEGEV].recoil = 0.1f;
	env->weapons[W_TEC9].recoil = 0.05f;
	env->weapons[W_FAMAS].max_ammos = 150;
	env->weapons[W_AK47].max_ammos = 150;
	env->weapons[W_SAWED_OFF].max_ammos = 60;
	env->weapons[W_GLOCK_18].max_ammos = 54;
	env->weapons[W_AUG].max_ammos = 180;
	env->weapons[W_UMP45].max_ammos = 160;
	env->weapons[W_MAG7].max_ammos = 72;
	env->weapons[W_GALIL].max_ammos = 200;
	env->weapons[W_NEGEV].max_ammos = 300;
	env->weapons[W_TEC9].max_ammos = 144;
}

void		assign_weapons_stats(t_env *env)
{
	damages_n_accuracy(env);
	magazine_n_reticle(env);
	cadency_n_shoot_mode(env);
	recoil_n_max_ammos(env);
}
