/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:08:03 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 15:14:38 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			get_spawn_position(t_map *map, char **line)
{
	t_vec3d			pos;

	if (ft_tablen(line) != 2)
	{
		ft_putendl_fd("Spawn location line corrupted", 2);
		return (-1);
	}
	pos = read_vec3d(line[1], '{', '}');
	if (pos.x == INFINITY || pos.y == INFINITY || pos.z == INFINITY)
		return (-1);
	map->spawn = pos;
	return (0);
}

int			get_cam_direction(t_map *map, char **line)
{
	t_vec2d			dir;

	if (ft_tablen(line) != 2)
	{
		ft_putendl_fd("Cam direction line corrupted", 2);
		return (-1);
	}
	dir = read_vec2d(line[1], '{', '}');
	if (dir.u == INFINITY || dir.v == INFINITY || dir.w == INFINITY)
		return (-1);
	map->cam_dir = dir;
	return (0);
}

int			check_line(t_env *env, t_mesh *m, char **stats)
{
	unsigned int	i;
	static int		(*mapper_fts[PS_MAX])(t_env*, t_mesh*, char*) = {
											NULL, mapper_position, mapper_speed,
											mapper_static, mapper_texture,
											mapper_deps};

	i = 1;
	while (stats[i])
	{
		if (mapper_fts[i](env, m, stats[i]))
			return (-1);
		i++;
	}
	return (0);
}
