/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creative.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:36:55 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/21 11:54:17 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		check_export(t_env *env, char *data)
{
	static char		*msgs[MAPERR_MAX] = {"Map saved",
											"Player should have one spawner"};
	t_ttf_config	*conf;
	static int		err_time = 0;
	static int		ret = 0;

	if (env->events.keys[KEY_M] && switch_mecontext(env, MAPED_SC_MENU))
		return (-1);
	else if (env->events.keys[KEY_P])
	{
		ret = export_maped_map(&env->edit_env);
		err_time = EXPORT_ERR_TIME;
		if (!ret && sound_system(env, SA_CHANGE,
			sp_fork(env->sound.volume, 2, env->cam.stats.pos)))
			return (-1);
	}
	if (err_time > 0)
	{
		conf = ttf_config();
		conf->size = 20;
		ft_strcpy((char*)conf->s, msgs[ret]);
		my_string_put(env, data, (t_point){200, 200}, FONT_COOLVETICA);
		err_time--;
	}
	return (0);
}

static void		refresh_last_gui(t_events *e, int *gui)
{
	if (e->keys[KEY_UP] || e->keys[KEY_DOWN] || e->buttons[BUTTON_SCLIC]
		|| e->buttons[BUTTON_SCROLL_DOWN] || e->buttons[BUTTON_SCROLL_UP])
		*gui = 100;
}

int				maped_creative(t_env *env)
{
	static int	last_gui_use = -1;

	if (sound_manager(env, SA_MAPED))
		return (-1);
	last_gui_use == -1 ? last_gui_use = 500 : 0;
	handle_creative_events(env);
	clear_screen_buffers(env);
	camera_aim(env);
	env->mid.mesh = NULL;
	if (rasterizer(env, &env->edit_env.map, false))
		return (-1);
	refresh_last_gui(&env->events, &last_gui_use);
	if (last_gui_use > 0)
	{
		draw_cg_pallet(env);
		render_pallets(env);
		last_gui_use--;
	}
	maped_crosshair(env);
	if (check_export(env, env->mlx.img_data))
		return (-1);
	mlx_put_image_to_window(env->mlx.mlx_ptr,
		env->mlx.mlx_win, env->mlx.img_ptr, 0, 0);
	return (0);
}
