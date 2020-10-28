/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:32:55 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 17:53:10 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	test_neighbours(t_ed_map *map, int x, int y, int z)
{
	if (x < 0 || x > map->width - 1
		|| y < 0 || y > map->height - 1
		|| z < 0 || z > map->depth - 1)
		return (1);
	return (map->map[x][y][z] != 163 && map->map[x][y][z] > BTXT_NONE);
}

static bool	full_neighbours(t_ed_map *map, int *pos)
{
	int	neighbours;

	neighbours = 0;
	neighbours += test_neighbours(map, pos[0] - 1, pos[1], pos[2]);
	neighbours += test_neighbours(map, pos[0] + 1, pos[1], pos[2]);
	neighbours += test_neighbours(map, pos[0], pos[1] - 1, pos[2]);
	neighbours += test_neighbours(map, pos[0], pos[1] + 1, pos[2]);
	neighbours += test_neighbours(map, pos[0], pos[1], pos[2] - 1);
	neighbours += test_neighbours(map, pos[0], pos[1], pos[2] + 1);
	return (neighbours == 6);
}

int			get_block_type(t_env *env, t_mesh *new, unsigned char type)
{
	int		ret;

	if (ft_inbounds(type, 0, 160))
		ret = (int)type % 32;
	else
		ret = type - 160 + BTXT_JUKEBOX - 1;
	if (env->context == C_CUSTOM)
		if (full_neighbours(&env->edit_env.new_map, new->m_pos))
			ret = BTXT_NONE;
	return (ret);
}

void		attribute_mesh(t_map *scene, int index)
{
	t_mesh		*mesh;
	t_triangle	*t;
	int			i;

	i = 0;
	mesh = dyacc(&scene->meshs, index);
	while (i < mesh->tris.nb_cells)
	{
		t = dyacc(&mesh->tris, i);
		t->mesh = mesh;
		i++;
	}
}
