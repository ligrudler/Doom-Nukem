/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:16:10 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 15:17:25 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_game_over_buttons(t_env *env)
{
	t_go_env	*me_env;
	t_button	*b;
	t_sprite	*sps[3];

	me_env = &env->custom_env.go_env;
	b = &me_env->buttons[GO_BUTTON_YES];
	sps[0] = &env->sprites[SP_YES_ON];
	sps[1] = &env->sprites[SP_YES_HOVER];
	sps[2] = &env->sprites[SP_YES_OFF];
	init_button(b, (t_point){600, 510}, sps);
	b->r_down = (t_point){600 + env->sprites[SP_YES_ON].wdt,
		500 + env->sprites[SP_YES_ON].hgt};
	b = &me_env->buttons[GO_BUTTON_NO];
	sps[0] = &env->sprites[SP_NO_ON];
	sps[1] = &env->sprites[SP_NO_HOVER];
	sps[2] = &env->sprites[SP_NO_OFF];
	init_button(b, (t_point){800, 510}, sps);
	b->r_down = (t_point){200 + env->sprites[SP_NO_ON].wdt,
		500 + env->sprites[SP_NO_ON].hgt};
}

int			setup_custom(t_env *env)
{
	env->custom_env.env = env;
	init_game_over_buttons(env);
	env->custom_env.sub_context = CUSTOM_SC_MENU;
	return (0);
}
