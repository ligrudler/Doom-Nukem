/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_H
# define ASTAR_H

# include "main.h"

# define NEIGHBOURG 18

# define ASTAR_MAX_DIST 3

struct			s_node
{
	int			i;
	bool		bobstacle;
	bool		bvisited;
	float		globalgoal;
	float		localgoal;
	t_vec3d		pos;
	int			nghbr[NEIGHBOURG];
	t_node		*parent;
};

struct			s_pathfinding
{
	t_vec3d		dim;
	t_node		*start;
	t_node		*end;
	t_dynarray	d_astar;
	t_dynarray	d_nodes;
};

int				astar_init(t_env *env);
int				astar(t_pf *env);

int				astar_get_custom_nodes(t_ed_map map, t_pf *env);

void			nodes_neighbours(t_pf *env, t_node *node);

int				nodes_3d_1d(t_vec3d dim, t_vec3d pos);

void			astar_delvisited_nodes(t_dynarray *arr);
void			astar_reset(t_pf *env);

int				astar_compare(void *a, void *b);
int				nodes_compare(void *a, void *b);
void			astar_sort_dynarray(t_dynarray *arr,
		int (*compare)(void *a, void *b));

#endif
