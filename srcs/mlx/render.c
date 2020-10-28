/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 04:50:00 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 15:21:23 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	mesure_time(bool end)
{
	static clock_t	start;

	if (!end)
	{
		start = clock();
		return (0);
	}
	else
		return ((double)(clock() - start) / CLOCKS_PER_SEC);
}

int		render(void *param)
{
	static int				(*render_fts[C_MAX])(void*) = {render_ts,
									render_camp, render_custom, render_maped};
	static struct timeval	t;
	t_env					*env;
	t_data					*data;

	env = (t_env*)param;
	data = &env->data;
	gettimeofday(&t, NULL);
	data->spent = (t.tv_sec - data->time.tv_sec) * 1000;
	data->spent += (t.tv_usec - data->time.tv_usec) / 1000;
	data->spent /= 1000;
	gettimeofday(&data->time, NULL);
	if (env->events.keys[KEY_ESCAPE])
		exit_doom(env, NULL, 0, EXIT_SUCCESS);
	if (render_fts[((t_env*)param)->context](param))
		exit_doom(env, "render failed", 2, EXIT_SUCCESS);
	env->events.buttons[BUTTON_SCROLL_UP] = false;
	env->events.buttons[BUTTON_SCROLL_DOWN] = false;
	return (0);
}
