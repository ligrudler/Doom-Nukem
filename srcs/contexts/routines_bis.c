/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 01:53:57 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/21 18:09:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	custom_to_ts(t_env *env)
{
	if (sound_system(env, SA_BUTTON,
		sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		exit_doom(env, "error sound_system", 0, -1);
	mlx_mouse_show();
	ft_free_ctab(env->scroll.list);
	env->scroll.list = NULL;
	ft_strdel(&env->scroll.s_path);
}

void	map_editor_to_ts(t_env *env)
{
	if (sound_system(env, SA_BUTTON,
		sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		exit_doom(env, "error sound_system", 0, -1);
	ft_free_ctab(env->scroll.list);
	env->scroll.list = NULL;
	ft_strdel(&env->scroll.s_path);
}
