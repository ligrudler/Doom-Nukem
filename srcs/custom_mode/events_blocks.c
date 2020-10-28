/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_blocks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:42:17 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 14:43:40 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vec3d		get_block_center(t_event_block *block)
{
	t_vec3d		ret;

	ret.x = block->x * 2.0f;
	ret.y = block->y * 2.0f;
	ret.z = block->z * 2.0f;
	return (ret);
}

static int	parse_block_type(t_env *env, t_custom_env *c, t_event_block block,
																	int p[3])
{
	if (block.id == BE_MOB_SPAWNER)
		env->custom_env.game.nb_spawners++;
	if (block.id == BE_SPAWNER)
	{
		env->edit_env.map.spawn = vec_fmult((t_vec3d){p[0], p[1], p[2], 0}, 2);
		env->edit_env.map.spawn.y += PLAYER_SIZE;
	}
	if (c->events.byte_size == 0
			&& init_dynarray(&c->events, sizeof(t_event_block), 0))
		return (-1);
	block.index = c->events.nb_cells;
	if (c->events.byte_size > 0
		&& push_dynarray(&c->events, &block, false))
		return (-1);
	return (0);
}

static int	parse_event_block(t_env *env, t_ed_map *map, int p[3])
{
	t_custom_env	*c;
	t_event_block	block;
	unsigned char	id;

	c = &env->custom_env;
	id = map->map[p[0]][p[1]][p[2]];
	if (ft_inbounds(id, 160, 160 + NB_INTERACTIVES))
	{
		block.x = p[0];
		block.y = p[1];
		block.z = p[2];
		block.id = id - 160;
		return (parse_block_type(env, c, block, p));
	}
	return (0);
}

int			parse_events_blocks(t_env *env)
{
	t_ed_map	*map;
	int			i;
	int			j;
	int			k;

	i = -1;
	env->custom_env.game.nb_spawners = 0;
	map = &env->edit_env.new_map;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			k = -1;
			while (++k < map->depth)
				if (parse_event_block(env, map, (int[3]){i, j, k}))
					return (-1);
		}
	}
	return (0);
}

int			handle_block_events(t_env *env)
{
	static int		(*block_fts[BE_MAX])(t_env*, t_event_block*) = {NULL,
							handle_jukeboxs, handle_mystery_boxs, handle_doors,
							handle_lavas, NULL};
	t_event_block	*block;
	int				ret;
	int				i;
	int				j;

	i = 0;
	while (i < env->custom_env.events.nb_cells && (j = 1))
	{
		block = dyacc(&env->custom_env.events, i);
		while (j < BE_MAX && block_fts[j])
		{
			if ((ret = block_fts[j](env, block)))
				break ;
			else if (ret == -1)
				return (-1);
			j++;
		}
		if (ret)
			break ;
		i++;
	}
	return (0);
}
