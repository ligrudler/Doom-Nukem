/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_system_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int
	stop_sound(t_env *env, int source)
{
	t_sound	*sound;

	sound = dyacc(env->sound.sounds, source);
	if (sound == NULL)
		return (0);
	alSourceStop(sound->ambient);
	return (0);
}

int
	sound_volume(t_env *env, int source, t_sparam p)
{
	ALint	status;
	t_sound	*sound;

	sound = dyacc(env->sound.sounds, source);
	if (sound == NULL || p.sound == false)
		return (0);
	alGetSourcei(sound->ambient, AL_SOURCE_STATE, &status);
	if (status == AL_PLAYING)
	{
		sound->volume += p.volume;
		sound->volume = sound->volume > env->sound.volume
			? env->sound.volume : sound->volume;
		sound->volume = sound->volume < 0 ? 0 : sound->volume;
		alSourcef(sound->ambient, AL_GAIN, sound->volume);
		sound->pitch += p.pitch;
		sound->pitch = sound->pitch > 2 ? 2 : sound->pitch;
		sound->pitch = sound->pitch < 0 ? 0 : sound->pitch;
		alSourcef(sound->ambient, AL_PITCH, sound->pitch);
	}
	return (0);
}
