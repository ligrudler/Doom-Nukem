/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 02:24:28 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/08 20:30:49 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		key_press(int key, void *param)
{
	static int	(*key_press_fts[C_MAX])(int, void*) = {key_press_ts,
					key_press_camp, key_press_custom, key_press_maped};
	t_env		*env;

	env = ((t_env*)param);
	if (key == KEY_ESCAPE)
		exit_doom(env, NULL, 0, EXIT_SUCCESS);
	env->events.keys[key] = true;
	return (key_press_fts[env->context](key, param));
}

int		key_release(int key, void *param)
{
	static int	(*key_release_fts[C_MAX])(int, void*) = {key_release_ts,
					key_release_camp, key_release_custom, key_release_maped};
	t_env		*env;

	env = ((t_env*)param);
	env->events.keys[key] = false;
	return (key_release_fts[env->context](key, param));
}

int		mouse_press(int button, int x, int y, void *param)
{
	static int	(*mouse_press_fts[C_MAX])(int, int, int, void*) = {
										mouse_press_ts, mouse_press_camp,
										mouse_press_custom, mouse_press_maped};
	t_env		*env;

	env = ((t_env*)param);
	env->events.buttons[button] = true;
	return (mouse_press_fts[env->context](button, x, y, param));
}

int		mouse_release(int button, int x, int y, void *param)
{
	static int	(*mouse_release_fts[C_MAX])(int, int, int, void*) = {
									mouse_release_ts, mouse_release_camp,
									mouse_release_custom, mouse_release_maped};
	t_env		*env;

	env = ((t_env*)param);
	env->events.buttons[button] = false;
	return (mouse_release_fts[env->context](button, x, y, param));
}

int		mouse_position(int x, int y, void *param)
{
	static int	(*mouse_position_fts[C_MAX])(int, int, void*) = {
					mouse_position_ts, mouse_position_camp,
					mouse_position_custom, mouse_position_maped};
	t_env		*env;

	env = ((t_env*)param);
	env->events.mouse_pos = (t_point){x, y};
	return (mouse_position_fts[env->context](x, y, param));
}
