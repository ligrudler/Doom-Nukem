/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_kills_annoucements.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			enemies_kills_annoucements(t_env *env)
{
	int			source;
	static int	tmp = 0;

	if (env->custom_env.game.kill_delay > 0)
		--env->custom_env.game.kill_delay;
	if (env->custom_env.game.kill_delay == 0)
	{
		env->custom_env.game.kill_count = 0;
		return (0);
	}
	tmp = env->custom_env.game.kill_delay == KILL_DELAY - 1 ? 0 : tmp;
	source = env->custom_env.game.kill_count;
	source = source < 2 ? 0 : source;
	source = source > 5 ? 6 : source;
	if (source)
	{
		source += SA_DOUBLEKILL - 2;
		if (tmp == source)
			return (0);
		tmp = source;
		if (sound_system(env, source, sp_overall(SA_DOUBLEKILL, SA_WICKEDSICK,
				sp_play(env->sound.volume, PITCH, env->cam.stats.pos))))
			return (-1);
	}
	return (0);
}
