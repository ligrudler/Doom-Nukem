/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:41:22 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 17:49:53 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	me_menu_to_new_map(t_env *env)
{
	if (sound_system(env, SA_BUTTON,
		sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		return (-1);
	clear_dynarray(&env->ttfs.fields[0].str);
	clear_dynarray(&env->ttfs.fields[1].str);
	clear_dynarray(&env->ttfs.fields[2].str);
	clear_dynarray(&env->ttfs.fields[3].str);
	env->ttfs.fields[0].rendered = true;
	env->ttfs.fields[1].rendered = true;
	env->ttfs.fields[2].rendered = true;
	env->ttfs.fields[3].rendered = true;
	return (0);
}

int	me_menu_to_creative(t_env *env)
{
	if (sound_system(env, 0, sp_overall(0, SA_MAX, sp_stop())))
		return (-1);
	if (sound_system(env, SA_BUTTON,
		sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		return (-1);
	env->cam.stats.pos = zero_vector();
	env->cam.stats.pitch = 0;
	env->cam.stats.yaw = 0;
	env->mid.mesh = NULL;
	mlx_mouse_hide();
	return (0);
}

int	me_new_map_to_creative(t_env *env)
{
	if (sound_system(env, 0, sp_overall(0, SA_MAX, sp_stop())))
		return (-1);
	if (sound_system(env, SA_BUTTON,
		sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		return (-1);
	env->cam.stats.pos = zero_vector();
	env->cam.stats.pitch = 0;
	env->cam.stats.yaw = 0;
	env->mid.mesh = NULL;
	mlx_mouse_hide();
	return (0);
}

int	me_new_map_to_menu(t_env *env)
{
	if (sound_system(env, SA_BUTTON,
		sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		return (-1);
	clear_dynarray(&env->ttfs.fields[0].str);
	clear_dynarray(&env->ttfs.fields[1].str);
	clear_dynarray(&env->ttfs.fields[2].str);
	clear_dynarray(&env->ttfs.fields[3].str);
	env->ttfs.fields[0].rendered = false;
	env->ttfs.fields[1].rendered = false;
	env->ttfs.fields[2].rendered = false;
	env->ttfs.fields[3].rendered = false;
	return (0);
}

int	me_creative_to_menu(t_env *env)
{
	if (sound_system(env, 0, sp_overall(0, SA_MAX, sp_stop())))
		return (-1);
	if (sound_system(env, SA_BUTTON,
		sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		return (-1);
	free_maped(env);
	mlx_mouse_show();
	return (0);
}
