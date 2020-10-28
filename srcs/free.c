/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 05:31:43 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/21 22:51:41 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			free_mesh(t_mesh *m)
{
	if (m->name)
		free(m->name);
	if (m->tris.byte_size)
		free_dynarray(&m->tris);
	if (m->deps.byte_size)
		free_dynarray(&m->deps);
}

static void		free_map_childrens(t_map *map)
{
	t_mesh	*m;
	t_mtl	*mtl;
	int		i;

	i = 0;
	while (i < map->meshs.nb_cells)
	{
		m = dyacc(&map->meshs, i);
		free_mesh(m);
		i++;
	}
	i = 0;
	while (i < map->mtls.nb_cells)
	{
		mtl = dyacc(&map->mtls, i);
		free(mtl->name);
		i++;
	}
}

void			free_map(t_map *map)
{
	free_map_childrens(map);
	if (map->meshs.byte_size)
		free_dynarray(&map->meshs);
	if (map->txts.byte_size)
		free_dynarray(&map->txts);
	if (map->mtls.byte_size)
		free_dynarray(&map->mtls);
	if (map->stats)
		free(map->stats);
	if (map->stats_cpy)
		free(map->stats_cpy);
}

void			free_maped(t_env *env)
{
	if (env->edit_env.map.meshs.byte_size)
		free_map(&env->edit_env.map);
	if (env->edit_env.new_map.map)
		free_matrice(&env->edit_env.new_map);
	if (env->edit_env.new_map.name)
		free(env->edit_env.new_map.name);
	ft_memset(&env->edit_env.map, 0, sizeof(t_map));
	ft_memset(&env->edit_env.new_map, 0, sizeof(t_ed_map));
}

int				free_env(t_env *env)
{
	static void	(*free_context[C_MAX])(t_env*) = {NULL, free_cmp,
													free_custom, free_maped};
	int			i;

	i = 0;
	free_fields(env);
	free_cam(&env->cam);
	while (i < SP_MAX)
	{
		if (i < SCENE_MAX)
			free_map(&env->maps[i]);
		if (env->sprites)
			mlx_destroy_image(env->mlx.mlx_ptr, env->sprites[i].img_ptr);
		i++;
	}
	if (free_context[env->context])
		free_context[env->context](env);
	return (0);
}
