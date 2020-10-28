/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		assign_enemys_stats(t_custom_game *game, t_enemy *enemy, char type)
{
	static int		damages[ENEMY_MAX] = {
		[ENEMY_CORONA] = EDAMAGES_CORONA,
		[ENEMY_MAGE] = EDAMAGES_MAGE,
		[ENEMY_GOULE] = EDAMAGES_GOULE
	};

	enemy->hp = game->mobs_pv;
	enemy->speed = game->mobs_speed;
	enemy->damages = damages[(int)type];
}

int			enemy_map_mapper(char type)
{
	static int		map[ENEMY_MAX] = {
		[ENEMY_MAGE] = SCENE_MAGE,
		[ENEMY_CORONA] = SCENE_UGLY,
		[ENEMY_GOULE] = SCENE_GOULE
	};

	return (map[(int)type]);
}

static int	copy_mob_to_scene(t_env *env, t_map *map, t_map *mob, t_enemy *e)
{
	t_mesh		new;
	t_mesh		*m;
	int			i;

	i = 0;
	e->map_start = env->edit_env.map.nmesh;
	e->map_end = e->map_start + mob->nmesh;
	while (i < mob->meshs.nb_cells)
	{
		ft_memset(&new, 0, sizeof(t_mesh));
		m = dyacc(&mob->meshs, i);
		new.type = 1;
		new.index = e->map_start + i;
		if (init_dynarray(&new.tris, sizeof(t_triangle), 12)
				|| copy_triangles(map, mob, m, &new)
				|| push_dynarray(&map->meshs, &new, false))
			return (-1);
		assign_meshs(dyacc(&map->meshs, map->nmesh));
		translate_mesh(map, dyacc(&map->meshs, map->nmesh), e->pos);
		map->nmesh++;
		i++;
	}
	return (0);
}

static void	enemy_offset(t_enemy *mob)
{
	int			i;
	int			j;
	t_mesh		*mesh;
	t_triangle	*tri;

	i = mob->map_start - 1;
	while (++i < mob->map_end)
	{
		mesh = dyacc(&mob->map->meshs, i);
		j = -1;
		while (++j < mesh->tris.nb_cells)
		{
			tri = dyacc(&mesh->tris, j);
			tri->points[0] = vec_add(tri->points[0], mob->offset);
			tri->points[1] = vec_add(tri->points[1], mob->offset);
			tri->points[2] = vec_add(tri->points[2], mob->offset);
		}
	}
}

int			create_mob(t_env *env, t_map *map, char type, t_vec3d pos)
{
	t_enemy	enemy;

	ft_memset((void *)&enemy, 0, sizeof(t_enemy));
	assign_enemys_stats(&env->custom_env.game, &enemy, type);
	enemy.head = (t_vec3d){ 0, 0, 1, 0 };
	enemy.offset = (t_vec3d){ 0, 1, 0, 0 };
	enemy.peace = 0;
	enemy.pos = pos;
	enemy.i = nodes_3d_1d(env->astar.dim, vec_fdiv(pos, 2));
	enemy.map = map;
	if (copy_mob_to_scene(env, map, &env->maps[enemy_map_mapper(type)], &enemy))
		return (-1);
	enemy_offset(&enemy);
	if (push_dynarray(&env->custom_env.mobs, &enemy, false))
		return (-1);
	return (0);
}
