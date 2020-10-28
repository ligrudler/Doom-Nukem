/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void
	nodes_init_nghbrs(t_pf *env)
{
	int		i;
	t_node	*node;

	astar_sort_dynarray(&env->d_nodes, nodes_compare);
	i = -1;
	while (++i < env->d_nodes.nb_cells)
	{
		node = dyacc(&env->d_nodes, i);
		nodes_neighbours(env, node);
	}
}

int
	nodes_init_dynarray(t_ed_map map, t_pf *env, int *pos)
{
	int		i;
	t_node	node;

	ft_memset(&node, 0, sizeof(t_node));
	node.pos = (t_vec3d) { pos[0], pos[1], pos[2], 0 };
	node.i = nodes_3d_1d(env->dim, node.pos);
	if (map.map[pos[0]][pos[1]][pos[2]])
		node.bobstacle = 1;
	i = -1;
	while (++i < NEIGHBOURG)
		node.nghbr[i] = -1;
	return (push_dynarray(&env->d_nodes, &node, 0));
}

int
	astar_get_custom_nodes(t_ed_map map, t_pf *env)
{
	int	pos[3];

	if (init_dynarray(&env->d_nodes, sizeof(t_node),
				map.width * map.height * map.depth))
		return (-1);
	env->dim = (t_vec3d){ map.width, map.height, map.depth, 0 };
	pos[0] = -1;
	while (++pos[0] < map.width)
	{
		pos[1] = -1;
		while (++pos[1] < map.height)
		{
			pos[2] = -1;
			while (++pos[2] < map.depth)
			{
				if (nodes_init_dynarray(map, env, pos))
					return (-1);
			}
		}
	}
	nodes_init_nghbrs(env);
	return (0);
}
