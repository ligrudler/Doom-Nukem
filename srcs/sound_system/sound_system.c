/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int
	init_sound_system(t_env *env, t_dynarray *sounds, int size)
{
	int		i;
	ALuint	*sources;

	if (size < 1 || init_dynarray(sounds, sizeof(t_sound), size))
		return (-1);
	if (!(sources = (ALuint *)malloc(sizeof(ALuint) * size)))
		return (-1);
	alGenSources(size - 1, sources);
	alDistanceModel(AL_LINEAR_DISTANCE);
	i = -1;
	while (++i < size)
		if (init_sound(env, sounds, sources, i))
		{
			free(sources);
			return (-1);
		}
	free(sources);
	return (0);
}

static int
	quit_sound_system(t_env *env)
{
	delete_sources(env->sound.sounds);
	free_dynarray(env->sound.sounds);
	delete_sources(env->sound.fork);
	free_dynarray(env->sound.fork);
	return (-1);
}

static int
	sound_overall(t_env *env, int source, t_sparam p)
{
	int			i;
	ALint		status;
	t_sound		*sound;

	i = p.start - 1;
	while (++i <= p.end && i < env->sound.sounds->nb_cells)
	{
		sound = dyacc(env->sound.sounds, i);
		if (p.no_sound)
		{
			alGetSourcei(sound->ambient, AL_SOURCE_STATE, &status);
			if (status == AL_PLAYING)
				return (1);
			continue ;
		}
		if ((sound_volume(env, sound->ambient, p))
				|| ((p.play || p.fork || p.stop)
					&& stop_sound(env, sound->ambient)))
			return (quit_sound_system(env));
	}
	if ((fork_sound(env, source, p)) || (play_sound(env, source, p)))
		return (quit_sound_system(env));
	return (0);
}

int
	sound_system(t_env *env, int source, t_sparam param)
{
	static t_dynarray	sounds;
	static t_dynarray	fork;

	if (sounds.byte_size == 0)
	{
		if (init_sound_system(env, &sounds, SA_MAX)
				|| init_sound_system(env, &fork, SA_BUFFER))
			return (quit_sound_system(env));
		env->sound.volume = VOLUME;
		env->sound.volume = env->sound.volume < 0 ? 0 : env->sound.volume;
		env->sound.volume = env->sound.volume > 1 ? 1 : env->sound.volume;
		env->sound.sounds = &sounds;
		env->sound.fork = &fork;
	}
	if (source < 0 || source > sounds.nb_cells - 1)
		return (!quit_sound_system(env));
	if (param.overall || param.no_sound)
		return (sound_overall(env, source, param));
	if ((sound_volume(env, source, param))
			|| (fork_sound(env, source, param))
			|| (play_sound(env, source, param))
			|| (param.stop && stop_sound(env, source)))
		return (quit_sound_system(env));
	return (0);
}
