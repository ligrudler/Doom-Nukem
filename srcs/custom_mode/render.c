/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:37:10 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 15:15:08 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_custom_routines(
						int (*routines[CUSTOM_SC_MAX][CUSTOM_SC_MAX])(t_env*))
{
	routines[CUSTOM_SC_MENU][CUSTOM_SC_PLAY] = custom_menu_to_play;
	routines[CUSTOM_SC_PLAY][CUSTOM_SC_MENU] = custom_play_to_menu;
	routines[CUSTOM_SC_PLAY][CUSTOM_SC_GAME_OVER] = custom_play_to_game_over;
	routines[CUSTOM_SC_GAME_OVER][CUSTOM_SC_PLAY] = custom_game_over_to_play;
	routines[CUSTOM_SC_GAME_OVER][CUSTOM_SC_MENU] = custom_game_over_to_menu;
}

int			switch_custom_context(t_env *env, unsigned int i)
{
	t_custom_env		*custom_env;
	static bool			first = true;
	static int			(*routines[CUSTOM_SC_MAX][CUSTOM_SC_MAX])(t_env*);

	custom_env = &env->custom_env;
	if (first)
		init_custom_routines(routines);
	if (i >= CUSTOM_SC_MAX)
	{
		ft_putendl_fd(ICS_ERR, 2);
		return (-1);
	}
	if (routines[custom_env->sub_context][i])
		if (routines[custom_env->sub_context][i](env))
			return (-1);
	env->custom_env.sub_context = i;
	first = false;
	return (0);
}

int			render_custom(void *param)
{
	static int	(*sub_contexts[CUSTOM_SC_MAX])(t_env *env) = {custom_menu,
												custom_play, custom_game_over};
	t_env		*env;

	env = ((t_env*)param);
	return (sub_contexts[env->custom_env.sub_context](env));
}
