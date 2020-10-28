/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		enemies_to_scene(t_env *env, t_dynarray *mobs)
{
	int		i;
	int		j;
	t_mesh	*mesh;
	t_enemy	*mob;

	i = -1;
	while (++i < mobs->nb_cells)
	{
		mob = dyacc(mobs, i);
		if (enemies_animations(env, mob))
			return (-1);
		j = mob->map_start - 1;
		while (++j < mob->map_end)
		{
			mesh = dyacc(&mob->map->meshs, j);
			translate_mesh(mob->map, mesh, vec_sub(mob->pos, mesh->corp.pos));
		}
	}
	return (0);
}

static void		find_random_spawner(t_dynarray *events, int sp[3], int index)
{
	t_event_block	*block;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (i < events->nb_cells)
	{
		block = dyacc(events, i);
		if (block->id == BE_MOB_SPAWNER)
			j++;
		if (j == index)
		{
			sp[0] = block->x;
			sp[1] = block->y;
			sp[2] = block->z;
			return ;
		}
		i++;
	}
}

static int		spawn_mob(t_env *env)
{
	t_custom_game	*game;
	int				index;
	int				p[3];
	t_vec3d			pos;

	game = &env->custom_env.game;
	if (game->nb_spawners == 0)
		return (0);
	index = rand() % game->nb_spawners + 1;
	find_random_spawner(&env->custom_env.events, p, index);
	pos.x = p[0] + p[0];
	pos.y = p[1] + p[1];
	pos.z = p[2] + p[2];
	pos.x = (int)pos.x % 2 ? pos.x + 1 : pos.x;
	pos.y = (int)pos.y % 2 ? pos.y + 1 : pos.y;
	pos.z = (int)pos.z % 2 ? pos.z + 1 : pos.z;
	if (vec_outrange(vec_add(env->astar.dim, env->astar.dim), pos))
		return (0);
	game->current_lmob--;
	return (create_mob(env, &env->edit_env.map, enemy_wave(env), pos));
}

int				handle_enemies(t_env *env)
{
	env->player.hover = false;
	env->player.hitmarker--;
	if (env->custom_env.spawner <= 0.0f)
	{
		if (env->custom_env.mobs.nb_cells < MAX_ENEMIES
			&& env->custom_env.game.current_lmob > 0 && spawn_mob(env))
			return (-1);
		env->custom_env.spawner = env->custom_env.game.spawn_speed;
	}
	else
		env->custom_env.spawner -= env->data.spent;
	if (env->custom_env.mobs.nb_cells)
	{
		if (env->mid.mesh && enemies_damages(env))
			return (-1);
		enemies_movements(env, &env->astar);
		if (enemies_death(env, &env->custom_env.mobs)
			|| enemies_to_scene(env, &env->custom_env.mobs)
			|| enemies_kills_annoucements(env))
			return (-1);
	}
	return (0);
}
