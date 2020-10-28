/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_animations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool			enemies_down(t_enemy *mob)
{
	if (mob->pos.y <= mob->down)
		return (true);
	mob->pos.y -= mob->speed / 2;
	return (false);
}

bool			enemies_up(t_enemy *mob)
{
	if (mob->pos.y >= mob->up)
		return (true);
	mob->pos.y += mob->speed / 2;
	return (false);
}

int				enemies_animations(t_env *env, t_enemy *mob)
{
	if (mob->end)
	{
		mob->down = 0;
		mob->up = 0;
		return (0);
	}
	if (mob->noise++ == ENEMIES_NOISE_DELAY)
	{
		if (sound_system(env, SA_LEVITATION, sp_fork(0.1f, 1, mob->pos)))
			return (-1);
		mob->noise = 0;
	}
	if (mob->down == 0)
		mob->down = mob->pos.y - MOB_ANIMATION_DOWN;
	if (mob->up == 0)
		mob->up = mob->pos.y + MOB_ANIMATION_UP;
	if (mob->up_token == false && enemies_up(mob))
		mob->up_token = true;
	if (mob->up_token == true && enemies_down(mob))
		mob->up_token = false;
	return (0);
}
