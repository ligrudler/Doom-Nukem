/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		astar_stock_neighbour(t_dynarray *arr, t_node *ngbhr)
{
	int	i;

	i = -1;
	while (++i < arr->nb_cells)
	{
		if (((t_node *)dyacc(arr, i))->i == ngbhr->i)
			return (0);
	}
	return (push_dynarray(arr, ngbhr, 0));
}

static int		astar_neighbour(t_pf *env, t_node **c, int i)
{
	float	plowergoal;
	t_node	*nghbr;

	nghbr = dyacc(&env->d_nodes, (*c)->nghbr[i]);
	if (nghbr == NULL)
		return (0);
	plowergoal = (*c)->localgoal + vec3d_dist((*c)->pos, nghbr->pos);
	if (plowergoal < nghbr->localgoal)
	{
		nghbr->localgoal = plowergoal;
		nghbr->globalgoal = nghbr->localgoal
			+ vec3d_dist(nghbr->pos, env->end->pos);
		nghbr->parent = dyacc(&env->d_nodes, (*c)->i);
	}
	if (nghbr->bvisited == 0 && nghbr->bobstacle == 0
		&& astar_stock_neighbour(&env->d_astar, nghbr))
		return (-1);
	*c = env->d_astar.c;
	return (0);
}

static bool		astar_exit(t_pf *env, t_node *current)
{
	if (vec3d_dist(env->start->pos, current->pos) > ASTAR_MAX_DIST)
	{
		env->end = NULL;
		return (true);
	}
	return (current->i == env->end->i
			|| env->d_astar.nb_cells < 1);
}

static int		astar_solve(t_pf *env, t_node *c)
{
	int	i;

	astar_sort_dynarray(&env->d_astar, astar_compare);
	astar_delvisited_nodes(&env->d_astar);
	c = env->d_astar.c;
	c->bvisited = 1;
	((t_node *)dyacc(&env->d_nodes, c->i))->bvisited = 1;
	if (astar_exit(env, c))
		return (1);
	i = -1;
	while (++i < NEIGHBOURG)
		if (astar_neighbour(env, &c, i))
			return (-1);
	return (0);
}

int				astar(t_pf *env)
{
	t_node	*current;
	int		ret;

	if (env->start == NULL || env->end == NULL)
		return (0);
	astar_reset(env);
	if (push_dynarray(&env->d_astar, env->start, 0))
		return (-1);
	current = env->d_astar.c;
	if (current == NULL)
		return (0);
	current->localgoal = 0;
	current->globalgoal = vec3d_dist(env->start->pos, env->end->pos);
	while ((ret = astar_solve(env, current)) == 0)
		;
	return (ret);
}
