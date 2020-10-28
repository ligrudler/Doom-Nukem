/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:32:51 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:35:32 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	snow(t_env *env, int *img, int size)
{
	static int	colors[7] = {0x222222, 0x444444, 0x666666, 0x888888, 0xaaaaaa,
															0xcccccc, 0xffffff};
	int			i;

	i = 0;
	if (*snow_play() && !(*snow_play() = 0) && sound_system(env, SA_SNOW,
		sp_fork(env->sound.volume / 2, 1, env->cam.stats.pos)))
		return (-1);
	while (i < size)
	{
		img[i] = colors[rand() % 6];
		i++;
	}
	return (0);
}

static void	get_step(t_env *env, float left_time, int *step)
{
	static float	t = INFINITY;

	if (t == INFINITY)
		t = left_time;
	t -= env->data.spent;
	if (*step == 0)
	{
		if (sound_system(env, SA_SNOW, sp_stop()))
			exit_doom(env, "error sound_system", 0, -1);
		if (sound_system(env, SA_CMP_INTRO,
			sp_play(env->sound.volume, 1, env->cam.stats.pos)))
			exit_doom(env, "error sound_system", 0, -1);
	}
	if (t <= 0)
	{
		*step += 1;
		t = INFINITY;
	}
}

int			cmp_intro(t_env *env)
{
	static float	time_list[INTRO_LIST_SIZE + 1] = {1.5f, 4, 6, 6, 6, 7, 4,
																	6, 3, 1.5f};
	static int		step = 0;

	if (sound_manager(env, SA_MAX))
		return (-1);
	get_step(env, time_list[step], &step);
	if (step == INTRO_LIST_SIZE + 1 || env->events.keys[KEY_P])
	{
		if (sound_system(env, SA_CMP_INTRO, sp_stop()))
			exit_doom(env, "error sound_system", 0, -1);
		if (!(step = 0) && switch_campaign_subcontext(env, CMP_SC_GAME))
			return (-1);
	}
	if (step == INTRO_LIST_SIZE - 1)
		*snow_play() = true;
	if ((step == 0 || step == INTRO_LIST_SIZE)
		&& snow(env, (int*)env->mlx.img_data, env->data.data_size / 4))
		return (-1);
	else if (step > 0 && step < INTRO_LIST_SIZE)
		map_sprite(env->mlx.img_data,
			env->sprites[SP_CMP_KEY + step], (t_point){0, 0});
	mlx_put_image_to_window(env->mlx.mlx_ptr,
		env->mlx.mlx_win, env->mlx.img_ptr, 0, 0);
	return (0);
}
