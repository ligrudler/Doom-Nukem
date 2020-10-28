/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:18:51 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/21 18:38:15 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		sound_button(t_env *env, bool hover)
{
	if (hover == false)
	{
		if (sound_system(env, SA_BUTTON, sp_stop()))
			return (-1);
		if (sound_system(env, SA_BUTTON,
				sp_play(env->sound.volume, PITCH, env->cam.stats.pos)))
			return (-1);
	}
	return (0);
}

static int		handle_events(t_env *env)
{
	static bool	clic = false;
	int			i;

	i = -1;
	while (++i < TS_BUTTON_MAX)
		if (is_on_button(env->events.mouse_pos, env->ts_env.buttons[i]))
		{
			if (sound_button(env, env->ts_env.buttons[i].is_hover))
				return (-1);
			if (!env->events.buttons[BUTTON_LCLIC] && clic)
			{
				if (i == TS_BUTTON_QUIT)
					exit_doom(env, NULL, 1, 0);
				else if (switch_context(env, i + 1))
					return (-1);
				clic = false;
				return (1);
			}
			clic = env->events.buttons[BUTTON_LCLIC];
			env->ts_env.buttons[i].is_hover = true;
		}
		else
			env->ts_env.buttons[i].is_hover = false;
	return (0);
}

static void		render_buttons(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < TS_BUTTON_MAX)
	{
		render_button(env, env->ts_env.buttons[i]);
		i++;
	}
}

static void		wait_frame(void)
{
	float		t;

	t = mesure_time(true);
	usleep(13500 - t);
}

int				render_ts(void *param)
{
	static int	anim = 120;
	t_env		*env;
	t_mlx		*mlx;
	int			ret;

	env = ((t_env*)param);
	mlx = &env->mlx;
	mesure_time(false);
	ret = handle_events(env);
	if (ret != 0)
		return (ret > 0 ? 0 : -1);
	map_sprite(mlx->img_data, env->sprites[SP_TS_BACKGROUND], (t_point){0, 0});
	if (anim > 0)
		animation(env);
	else
		map_sprite(mlx->img_data, env->sprites[SP_TS_LOGO], (t_point){180, 50});
	render_buttons(env);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->img_ptr, 0, 0);
	if (anim-- > 0)
		wait_frame();
	else if (sound_manager(env, SA_TITLE_SCREEN_L))
		return (-1);
	return (0);
}
