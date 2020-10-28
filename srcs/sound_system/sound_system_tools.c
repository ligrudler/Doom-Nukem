/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_system_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sparam
	sp_no_sound(int start, int end)
{
	int			tmp;
	t_sparam	param;

	ft_memset(&param, 0, sizeof(t_sparam));
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
	param.no_sound = true;
	return (param);
}

t_sparam
	sp_stop(void)
{
	t_sparam	param;

	ft_memset(&param, 0, sizeof(t_sparam));
	param.stop = true;
	return (param);
}

void
	delete_sources(t_dynarray *sounds)
{
	int		i;
	t_sound	*sound;

	i = -1;
	while (++i < sounds->nb_cells)
	{
		sound = dyacc(sounds, i);
		alDeleteSources(1, &sound->ambient);
	}
}

int
	init_sound(t_env *env, t_dynarray *s, ALuint *sources, int i)
{
	t_sound	sound;

	ft_memset(&sound, 0, sizeof(t_sound));
	sound.samples = &env->sound.samples[i];
	sound.ambient = sources[i];
	alSourcef(sound.ambient, AL_REFERENCE_DISTANCE, 1);
	alSourcef(sound.ambient, AL_ROLLOFF_FACTOR, 1);
	alSourcef(sound.ambient, AL_MAX_DISTANCE, 60);
	return (push_dynarray(s, &sound, 0));
}
