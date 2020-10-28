/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_system_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sparam		sp_fork(float volume, float pitch, t_vec3d pos)
{
	t_sparam	param;

	volume = volume > 1 ? 1 : volume;
	volume = volume < 0 ? 0 : volume;
	pitch = pitch > 2 ? 2 : pitch;
	pitch = pitch < 0 ? 0 : pitch;
	ft_memset(&param, 0, sizeof(t_sparam));
	param.fork = true;
	param.volume = volume;
	param.pitch = pitch;
	param.pos = pos;
	return (param);
}

t_sparam		sp_overall(int start, int end, t_sparam p)
{
	int			tmp;
	t_sparam	param;

	param = p;
	start = start < 0 ? 0 : start;
	start = start > SA_MAX - 1 ? SA_MAX - 1 : start;
	end = end < 0 ? 0 : end;
	end = end > SA_MAX - 1 ? SA_MAX - 1 : end;
	if (end < start)
	{
		tmp = end;
		end = start;
		start = tmp;
	}
	param.start = start;
	param.end = end;
	param.overall = true;
	return (param);
}

t_sparam		sp_play(float volume, float pitch, t_vec3d pos)
{
	t_sparam	param;

	volume = volume > 1 ? 1 : volume;
	volume = volume < 0 ? 0 : volume;
	pitch = pitch > 2 ? 2 : pitch;
	pitch = pitch < 0 ? 0 : pitch;
	ft_memset(&param, 0, sizeof(t_sparam));
	param.play = true;
	param.volume = volume;
	param.pitch = pitch;
	param.pos = pos;
	return (param);
}

t_sparam		sp_volume(float volume, float pitch)
{
	t_sparam	param;

	volume = volume > 1 ? 1 : volume;
	volume = volume < -1 ? -1 : volume;
	pitch = pitch > 2 ? 2 : pitch;
	pitch = pitch < -2 ? -2 : pitch;
	ft_memset(&param, 0, sizeof(t_sparam));
	param.sound = true;
	param.volume = volume;
	param.pitch = pitch;
	return (param);
}
