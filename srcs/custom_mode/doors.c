/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:35:13 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 14:37:29 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_event_block	*find_event_block(t_env *env, int pos[3])
{
	t_event_block	*block;
	int				i;

	i = 0;
	while (i < env->custom_env.events.nb_cells)
	{
		block = dyacc(&env->custom_env.events, i);
		if (block->id == BE_DOOR && pos[0] == block->x
			&& pos[1] == block->y && pos[2] == block->z)
			return (block);
		i++;
	}
	return (NULL);
}

t_mesh					*get_blockindex(t_map *map, int *pos, int *m_index)
{
	t_mesh	*mesh;
	int		i;

	i = -1;
	while (++i < map->meshs.nb_cells)
	{
		mesh = dyacc(&map->meshs, i);
		if (mesh->m_pos[0] == pos[0]
				&& mesh->m_pos[1] == pos[1]
				&& mesh->m_pos[2] == pos[2])
		{
			*m_index = i;
			break ;
		}
	}
	return (mesh);
}

static void				del_recursif(t_env *env, int p[3])
{
	t_event_block	*block;
	t_node			*node;
	t_mesh			*m;
	int				i;

	if (p[0] < 0 || p[0] > env->edit_env.new_map.width - 1
		|| p[1] < 0 || p[1] > env->edit_env.new_map.height - 1
		|| p[2] < 0 || p[2] > env->edit_env.new_map.depth - 1)
		return ;
	m = get_blockindex(&env->edit_env.map, (int[3]){p[0], p[1], p[2]}, &i);
	if (m->type == BTXT_DOOR)
	{
		block = find_event_block(env, p);
		block->id = BE_MAX;
		node = dyacc(&env->astar.d_nodes,
			nodes_3d_1d(env->astar.dim, (t_vec3d){p[0], p[1], p[2], 0}));
		node->bobstacle = 0;
		m->type = BTXT_NONE;
		del_recursif(env, (int[3]){p[0] - 1, p[1], p[2]});
		del_recursif(env, (int[3]){p[0] + 1, p[1], p[2]});
		del_recursif(env, (int[3]){p[0], p[1] + 1, p[2]});
		del_recursif(env, (int[3]){p[0], p[1] - 1, p[2]});
		del_recursif(env, (int[3]){p[0], p[1], p[2] + 1});
		del_recursif(env, (int[3]){p[0], p[1], p[2] - 1});
	}
}

int						del_door(t_env *env, t_event_block *block)
{
	if (block->id == BE_DOOR)
	{
		del_recursif(env, (int[3]){block->x, block->y, block->z});
		if (sound_system(env, SA_DOOR,
			sp_fork(env->sound.volume, PITCH, env->cam.stats.pos)))
			return (-1);
	}
	return (0);
}
