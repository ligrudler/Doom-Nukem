/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int
	astar_init(t_env *env)
{
	t_pf		*astar;
	t_ed_map	map;

	astar = &env->astar;
	map = env->edit_env.new_map;
	if (init_dynarray(&astar->d_astar, sizeof(t_node), 1))
		return (-1);
	if (astar_get_custom_nodes(map, astar))
		return (-1);
	return (0);
}

void
	astar_delvisited_nodes(t_dynarray *arr)
{
	int	i;

	i = -1;
	while (++i < arr->nb_cells)
	{
		if (((t_node *)dyacc(arr, i))->bvisited)
			extract_dynarray(arr, i);
	}
}

void
	astar_reset(t_pf *env)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i < env->d_nodes.nb_cells)
	{
		node = dyacc(&env->d_nodes, i);
		node->bvisited = 0;
		node->globalgoal = INFINITY;
		node->localgoal = INFINITY;
		node->parent = NULL;
	}
	clear_dynarray(&env->d_astar);
}
