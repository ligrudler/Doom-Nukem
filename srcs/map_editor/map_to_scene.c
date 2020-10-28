/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:29:52 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 16:42:11 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		translate_triangle(t_mesh *new, t_triangle *t)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		t->points[i].x += new->m_pos[0] * 2;
		t->points[i].y += new->m_pos[1] * 2;
		t->points[i].z += new->m_pos[2] * 2;
		i++;
	}
}

static int	create_block(t_env *env, t_map *scene, unsigned char type, int *pos)
{
	t_mesh	new;
	int		i;

	i = 0;
	ft_memset(&new, 0, sizeof(t_mesh));
	ft_memcpy(new.m_pos, pos, sizeof(int) * 3);
	if ((ft_inbounds(type, 0, 31) || ft_inbounds(type, 160, 191))
		&& create_cube(env, &new, type))
		return (-1);
	else if (ft_inbounds(type, 32, 159) && create_slope(env, &new, type))
		return (-1);
	if (env->context == C_CUSTOM)
		culling(env, &new, type);
	if (push_dynarray(&scene->meshs, &new, false))
		return (-1);
	attribute_mesh(scene, scene->nmesh);
	scene->nmesh = scene->meshs.nb_cells;
	return (0);
}

int			map_to_scene(t_env *env)
{
	t_edit_env	*edit_env;
	t_map		*scene;
	int			x;
	int			y;
	int			z;

	x = -1;
	edit_env = &env->edit_env;
	scene = &edit_env->map;
	if (init_dynarray(&scene->meshs, sizeof(t_mesh), MAX_CHUNKS))
		return (-1);
	while (++x < edit_env->new_map.width)
	{
		y = -1;
		while (++y < edit_env->new_map.height)
		{
			z = -1;
			while (++z < edit_env->new_map.depth)
				if (create_block(env, scene,
					edit_env->new_map.map[x][y][z], (int[3]){x, y, z}))
					return (-1);
		}
	}
	scene->spawn = (t_vec3d){0, 0, 0, 0};
	return (0);
}
