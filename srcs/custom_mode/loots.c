/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:54:49 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 14:56:52 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			init_loots(t_env *env)
{
	t_vec3d	pos;
	t_mesh	*m;
	int		i;

	i = 0;
	pos = (t_vec3d){0, 0, 0, 0};
	if (!(m = copy_to_scene(&env->edit_env.map, &env->maps[SCENE_LOOT], pos)))
		return (-1);
	while (i < LOOT_MAX)
	{
		env->custom_env.loots[i] = m;
		m = dyacc(&env->edit_env.map.meshs, m->index + 1);
		i++;
	}
	return (0);
}

static void	loot_death(t_env *env, t_loot *loot)
{
	t_vec3d	v;

	v = vec_fmult(loot->m->corp.pos, -1.0f);
	translate_mesh(&env->edit_env.map, loot->m, v);
	ft_bzero(loot, sizeof(t_loot));
}

static int	launch_loot(t_env *env, t_loot *loot)
{
	static int	(*loots_fts[LOOT_MAX])(t_env*) = {loot_nuke, loot_money,
													loot_shield, loot_ammos};
	int			ret;

	ret = loots_fts[(int)loot->id](env);
	loot_death(env, loot);
	return (ret);
}

int			spawn_loot(t_env *env, t_vec3d pos)
{
	t_loot		*loot;
	t_map		*map;

	loot = &env->custom_env.loot;
	if (loot->on || rand() % LOOT_FREQ > 0)
		return (0);
	map = &env->maps[SCENE_LOOT];
	loot->id = rand() % LOOT_MAX;
	loot->m = env->custom_env.loots[(int)loot->id];
	loot->on = true;
	loot->left = LOOT_LIFETIME;
	pos.y += 4.0f;
	translate_mesh(&env->edit_env.map, loot->m, pos);
	return (0);
}

int			handle_loots(t_env *env)
{
	t_loot			*loot;
	t_vec3d			diff;
	float			dist;

	loot = &env->custom_env.loot;
	if (loot->m)
	{
		loot->left -= env->data.spent;
		rotate_mesh(loot->m, loot->m->corp.pos,
			LOOT_LIFETIME / loot->left / 10, rotate_y);
		if (loot->left <= 0)
			loot_death(env, loot);
		else if ((dist = vec3d_dist(env->cam.stats.pos,
			loot->m->corp.pos)) < EVENT_DIST)
		{
			diff = vec_sub(env->cam.stats.pos, loot->m->corp.pos);
			translate_mesh(&env->edit_env.map,
				loot->m, vec_fmult(diff, 0.33f / dist));
			if (dist < 0.2f)
				return (launch_loot(env, loot));
		}
	}
	return (0);
}
