/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:59:44 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 16:03:21 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	select_map(t_env *env)
{
	t_scroll	*s;

	s = &env->scroll;
	display_file(env);
	if (s->s_path)
	{
		if (import_maped_map(&env->edit_env, s->s_path)
			|| !(env->custom_env.map_path = ft_strdup(s->s_path)))
			exit_doom(env, "Parsing Failed for a custom map", 2, EXIT_FAILURE);
		if (switch_custom_context(env, CUSTOM_SC_PLAY))
			return (-1);
	}
	ft_strdel(&s->s_path);
	return (0);
}

static int	handle_events(t_env *env)
{
	static bool	clic = false;
	int			i;

	i = -1;
	while (++i < MAPED_MENU_BUTTON_MAX)
		if (is_on_button(env->events.mouse_pos, env->edit_env.buttons[i]))
		{
			if (!env->events.buttons[BUTTON_LCLIC] && clic)
			{
				if (i == MAPED_MENU_BUTTON_MAIN_MENU
					&& switch_context(env, C_TITLE_SCREEN))
					return (-1);
				clic = false;
				return (1);
			}
			clic = env->events.buttons[BUTTON_LCLIC];
			env->edit_env.buttons[i].is_hover = true;
		}
		else
			env->edit_env.buttons[i].is_hover = false;
	return (0);
}

int			custom_menu(t_env *env)
{
	t_point	p;

	p = (t_point){0, 0};
	if (sound_manager(env, SA_TITLE_SCREEN_L))
		return (-1);
	if (handle_events(env))
		return (0);
	map_sprite(env->mlx.img_data, env->sprites[SP_CUSTOM_BACKGROUND], p);
	render_button(env, env->edit_env.buttons[MAPED_MENU_BUTTON_MAIN_MENU]);
	if (select_map(env))
		return (-1);
	mlx_put_image_to_window(env->mlx.mlx_ptr,
		env->mlx.mlx_win, env->mlx.img_ptr, 0, 0);
	return (0);
}
