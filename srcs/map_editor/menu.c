/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:02:32 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 16:12:28 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
				else if (i == MAPED_MENU_BUTTON_NEW_MAP
					&& switch_mecontext(env, MAPED_SC_NEW_MAP))
					return (-1);
				clic = false;
				return (0);
			}
			clic = env->events.buttons[BUTTON_LCLIC];
			env->edit_env.buttons[i].is_hover = true;
		}
		else
			env->edit_env.buttons[i].is_hover = false;
	return (0);
}

static void	render_buttons(t_env *env)
{
	render_button(env, env->edit_env.buttons[MAPED_MENU_BUTTON_NEW_MAP]);
	render_button(env, env->edit_env.buttons[MAPED_MENU_BUTTON_MAIN_MENU]);
}

static int	select_map(t_env *env)
{
	t_scroll	*s;

	s = &env->scroll;
	display_file(env);
	if (s->s_path)
	{
		if (import_maped_map(&env->edit_env, s->s_path)
			|| map_to_scene(env) || switch_mecontext(env, MAPED_SC_CREATIVE))
			return (-1);
	}
	ft_strdel(&s->s_path);
	return (0);
}

int			maped_menu(t_env *env)
{
	char	*data;

	data = env->mlx.img_data;
	if (sound_manager(env, SA_TITLE_SCREEN_L))
		return (-1);
	if (handle_events(env))
		return (-1);
	map_sprite(data, env->sprites[SP_ME_BACKGROUND], (t_point){0, 0});
	map_sprite(data, env->sprites[SP_ME_MENU_TITLE], (t_point){420, 60});
	if (select_map(env))
		return (-1);
	render_buttons(env);
	mlx_put_image_to_window(env->mlx.mlx_ptr,
		env->mlx.mlx_win, env->mlx.img_ptr, 0, 0);
	return (0);
}
