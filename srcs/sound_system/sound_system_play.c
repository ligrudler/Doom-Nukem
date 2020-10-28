/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_system_play.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int
	source_param(ALuint *source, t_sparam p)
{
	float	vec[6];

	alSource3f(*source, AL_POSITION, p.pos.x, p.pos.y, p.pos.z);
	alSource3f(*source, AL_VELOCITY, 0, 0, 0);
	alSource3f(*source, AL_DIRECTION, 0, 0, 1);
	vec[0] = 0;
	vec[1] = 0;
	vec[2] = 1;
	vec[3] = 0;
	vec[4] = 1;
	vec[5] = 0;
	alSourcefv(*source, AL_ORIENTATION, vec);
	return (0);
}

static int
	sound_param(t_env *env, ALuint *source, t_sparam p)
{
	float	vec[6];

	alListener3f(AL_POSITION, env->cam.stats.pos.x,
			env->cam.stats.pos.y, env->cam.stats.pos.z);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListener3f(AL_DIRECTION, env->cam.stats.dir.x,
			env->cam.stats.dir.y, env->cam.stats.dir.z);
	vec[0] = env->cam.stats.dir.x;
	vec[1] = env->cam.stats.dir.y;
	vec[2] = env->cam.stats.dir.z;
	vec[3] = 0;
	vec[4] = 1;
	vec[5] = 0;
	alListenerfv(AL_ORIENTATION, vec);
	if (source_param(source, p))
		return (-1);
	alSourcef(*source, AL_GAIN, p.volume);
	alSourcef(*source, AL_PITCH, p.pitch);
	return (0);
}

static int
	reset_fork(t_env *env)
{
	int		i;
	ALuint	*sources;
	t_sound	*sound;

	delete_sources(env->sound.fork);
	if (!(sources = (ALuint *)malloc(sizeof(ALuint) * SA_BUFFER)))
		return (-1);
	alGenSources(SA_BUFFER - 1, sources);
	i = -1;
	while (++i < SA_BUFFER - 1)
	{
		sound = dyacc(env->sound.fork, i);
		if (init_sound(env, env->sound.fork, sources, i))
		{
			free(sources);
			return (-1);
		}
	}
	free(sources);
	return (0);
}

int
	fork_sound(t_env *env, int source, t_sparam p)
{
	t_sound		*sound;
	t_sound		*fork;
	static int	current = 0;

	if (p.fork == false)
		return (0);
	if ((sound = dyacc(env->sound.sounds, source)) == NULL)
		return (-1);
	if (current > SA_BUFFER - 1)
	{
		if (reset_fork(env))
			return (-1);
		current = 0;
	}
	if ((fork = dyacc(env->sound.fork, current++)) == NULL)
		return (-1);
	if (sound_param(env, &fork->ambient, p))
		return (-1);
	alSourcei(fork->ambient, AL_BUFFER, (ALint)sound->samples->buffer);
	alSourcePlay(fork->ambient);
	return (0);
}

int
	play_sound(t_env *env, int source, t_sparam p)
{
	ALint	status;
	t_sound	*sound;

	sound = dyacc(env->sound.sounds, source);
	if (sound == NULL || p.play == false)
		return (0);
	sound->volume = p.volume;
	sound->pitch = p.pitch;
	alGetSourcei(sound->ambient, AL_SOURCE_STATE, &status);
	if (status == AL_PLAYING)
		return (0);
	if (sound_param(env, &sound->ambient, p))
		return (-1);
	alSourcei(sound->ambient, AL_BUFFER, (ALint)sound->samples->buffer);
	alSourcePlay(sound->ambient);
	return (0);
}
