/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_neighbours.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void
	nodes_diagonals_xy(t_node *node, t_vec3d dim)
{
	int	x;
	int	y;
	int	z;

	x = node->pos.x;
	y = node->pos.y;
	z = node->pos.z;
	if (x > 0 && y > 0)
		node->nghbr[6] = nodes_3d_1d(dim, (t_vec3d){ x - 1, y - 1, z, 0 });
	if (x < dim.x - 1 && y < dim.y - 1)
		node->nghbr[7] = nodes_3d_1d(dim, (t_vec3d){ x + 1, y + 1, z, 0 });
	if (x < dim.x - 1 && y > 0)
		node->nghbr[8] = nodes_3d_1d(dim, (t_vec3d){ x + 1, y - 1, z, 0 });
	if (x > 0 && y < dim.y - 1)
		node->nghbr[9] = nodes_3d_1d(dim, (t_vec3d){ x - 1, y + 1, z, 0 });
}

static void
	nodes_diagonals_xz(t_node *node, t_vec3d dim)
{
	int	x;
	int	y;
	int	z;

	x = node->pos.x;
	y = node->pos.y;
	z = node->pos.z;
	if (x > 0 && z > 0)
		node->nghbr[10] = nodes_3d_1d(dim, (t_vec3d){ x - 1, y, z - 1, 0 });
	if (x < dim.x - 1 && z < dim.z - 1)
		node->nghbr[11] = nodes_3d_1d(dim, (t_vec3d){ x + 1, y, z + 1, 0 });
	if (x < dim.x - 1 && z > 0)
		node->nghbr[12] = nodes_3d_1d(dim, (t_vec3d){ x + 1, y, z - 1, 0 });
	if (x > 0 && z < dim.z - 1)
		node->nghbr[13] = nodes_3d_1d(dim, (t_vec3d){ x - 1, y, z + 1, 0 });
}

static void
	nodes_diagonals_yz(t_node *node, t_vec3d dim)
{
	int	x;
	int	y;
	int	z;

	x = node->pos.x;
	y = node->pos.y;
	z = node->pos.z;
	if (y > 0 && z > 0)
		node->nghbr[14] = nodes_3d_1d(dim, (t_vec3d){ x, y - 1, z - 1, 0 });
	if (y < dim.y - 1 && z < dim.z - 1)
		node->nghbr[15] = nodes_3d_1d(dim, (t_vec3d){ x, y + 1, z + 1, 0 });
	if (y < dim.y - 1 && z > 0)
		node->nghbr[16] = nodes_3d_1d(dim, (t_vec3d){ x, y + 1, z - 1, 0 });
	if (y > 0 && z < dim.z - 1)
		node->nghbr[17] = nodes_3d_1d(dim, (t_vec3d){ x, y - 1, z + 1, 0 });
}

static void
	nodes_neighbours_diagonals(t_node *node, t_vec3d dim)
{
	nodes_diagonals_xy(node, dim);
	nodes_diagonals_xz(node, dim);
	nodes_diagonals_yz(node, dim);
}

void
	nodes_neighbours(t_pf *env, t_node *node)
{
	int		x;
	int		y;
	int		z;
	t_vec3d	dim;

	x = node->pos.x;
	y = node->pos.y;
	z = node->pos.z;
	dim = env->dim;
	if (x > 0)
		node->nghbr[0] = nodes_3d_1d(dim, (t_vec3d){ x - 1, y, z, 0 });
	if (x < dim.x - 1)
		node->nghbr[1] = nodes_3d_1d(dim, (t_vec3d){ x + 1, y, z, 0 });
	if (y > 0)
		node->nghbr[2] = nodes_3d_1d(dim, (t_vec3d){ x, y - 1, z, 0 });
	if (y < dim.y - 1)
		node->nghbr[3] = nodes_3d_1d(dim, (t_vec3d){ x, y + 1, z, 0 });
	if (z > 0)
		node->nghbr[4] = nodes_3d_1d(dim, (t_vec3d){ x, y, z - 1, 0 });
	if (z < dim.z - 1)
		node->nghbr[5] = nodes_3d_1d(dim, (t_vec3d){ x, y, z + 1, 0 });
	if (NEIGHBOURG == 18)
		nodes_neighbours_diagonals(node, dim);
}
