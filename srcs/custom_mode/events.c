/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:37:15 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/13 14:26:21 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		key_press_custom(int key, void *param)
{
	t_env	*env;

	env = ((t_env*)param);
	if (env->custom_env.sub_context == CUSTOM_SC_PLAY && key == KEY_Q)
		env->data.wireframe = !env->data.wireframe;
	return (0);
}

int		key_release_custom(int key, void *param)
{
	t_env	*env;

	env = ((t_env*)param);
	(void)key;
	return (0);
}

int		mouse_press_custom(int button, int x, int y, void *param)
{
	t_env	*env;

	env = ((t_env*)param);
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

int		mouse_release_custom(int button, int x, int y, void *param)
{
	t_env	*env;

	env = ((t_env*)param);
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

int		mouse_position_custom(int x, int y, void *param)
{
	t_env	*env;

	env = ((t_env*)param);
	env->events.mouse_pos = (t_point){x, y};
	(void)x;
	(void)y;
	return (0);
}
