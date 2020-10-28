/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:14:13 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:17:14 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		free_matrice(t_ed_map *env)
{
	int		i;
	int		j;

	if (env->map == NULL)
		return ;
	i = 0;
	while (i < env->width)
	{
		j = 0;
		while (j < env->height)
		{
			free(env->map[i][j]);
			j++;
		}
		free(env->map[i]);
		i++;
	}
	free(env->map);
	env->map = NULL;
}

int			init_matrice(t_ed_map *env)
{
	int		x;
	int		y;
	int		size;
	int		error;

	error = 0;
	if (!(env->map = ft_memalloc(sizeof(unsigned char**) * env->width)))
		error = 1;
	x = -1;
	while (error == 0 && ++x < env->width)
	{
		if (!(env->map[x] = ft_memalloc(sizeof(unsigned char*) * env->height)))
			error = 1;
		y = -1;
		while (error == 0 && ++y < env->height)
		{
			size = sizeof(unsigned char) * env->depth;
			if (!(env->map[x][y] = ft_memalloc(size)))
				error = 1;
		}
	}
	if (error == 1)
		free_matrice(env);
	return (error == 1 ? 0 : 1);
}

static void	fill_map_bottom(t_ed_map *new)
{
	int		x;
	int		z;

	x = 0;
	while (x < new->width)
	{
		z = 0;
		while (z < new->depth)
		{
			new->map[x][0][z] = BTXT_OBSIDIENNE;
			z++;
		}
		x++;
	}
}

int			build_map(t_env *env, t_ed_map *new)
{
	if (!init_matrice(new))
		return (-1);
	fill_map_bottom(new);
	if (map_to_scene(env))
		return (-1);
	return (0);
}
