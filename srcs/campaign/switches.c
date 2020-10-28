/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switches.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:33:33 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:39:18 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				switch_bit(t_env *env, t_buzzer *b, bool sound)
{
	t_triangle	*t;
	int			i;

	i = 0;
	b->on = !b->on;
	if (sound && sound_system(env, SA_CMP_BUTTON,
		sp_fork(env->sound.volume * 2, 1, env->cmp_env.door)))
		return (-1);
	while (i < b->start->tris.nb_cells)
	{
		t = dyacc(&b->start->tris, i);
		t->color = b->on ? 0x00ff00 : 0xff0000;
		i++;
	}
	i = 0;
	while (i < b->buzzer->tris.nb_cells)
	{
		t = dyacc(&b->buzzer->tris, i);
		t->color = b->on ? 0x00ff00 : 0xff0000;
		i++;
	}
	return (0);
}

static t_buzzer	*get_closest_switch(t_env *env, float *d)
{
	int			index;
	float		tmp;
	int			i;

	i = 0;
	*d = INFINITY;
	while (i < NB_BUZZERS)
	{
		tmp = vec3d_dist(env->cam.stats.pos, env->cmp_env.buzzers[i].pos);
		if (tmp < *d)
		{
			index = i;
			*d = tmp;
		}
		i++;
	}
	return (&env->cmp_env.buzzers[index]);
}

void			handle_enigma(t_env *env)
{
	static bool		answer[NB_BUZZERS] = {1, 0, 1, 0, 1, 0};
	bool			try[NB_BUZZERS];
	int				i;

	i = 0;
	while (i < NB_BUZZERS)
	{
		try[i] = env->cmp_env.buzzers[i].on;
		i++;
	}
	if (!ft_memcmp(answer, try, NB_BUZZERS))
		env->cmp_env.done = true;
}

int				handle_switches(t_env *env)
{
	static float	delay = 0;
	t_buzzer		*buzz;
	float			dist;

	delay -= env->data.spent;
	if (env->scene != SCENE_DUST
		|| delay > 0 || !(buzz = get_closest_switch(env, &dist)))
		return (0);
	if (dist < 1)
	{
		textual_hint(env, "E",
			buzz->on ? "switch bit off" : "switch bit on", 0);
		if (env->events.keys[KEY_E])
		{
			delay = 0.5f;
			if (switch_bit(env, buzz, true))
				return (-1);
		}
	}
	return (0);
}
