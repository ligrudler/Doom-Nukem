/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:50:02 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/18 18:12:27 by grudler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		free_cam(t_cam *cam)
{
	int		i;

	if (cam->clip_arrs[0].byte_size)
	{
		i = -1;
		while (++i < 4)
			free_dynarray(&cam->clip_arrs[i]);
	}
	if (cam->to_clip.byte_size)
		free_dynarray(&cam->to_clip);
	if (cam->to_raster.byte_size)
		free_dynarray(&cam->to_raster);
	if (cam->z_buffer)
		free(cam->z_buffer);
}

void		free_fields(t_env *env)
{
	int		i;

	i = 0;
	while (i < FIELD_MAX)
	{
		free(env->ttfs.fields[i].name);
		free_dynarray(&env->ttfs.fields[i].str);
		i++;
	}
	input_fields(env, false, true);
}

void		free_player(t_player *p)
{
	t_weapon	*w;
	int			i;

	i = 0;
	while (i < p->weapons.nb_cells)
	{
		w = dyacc(&p->weapons, i);
		free(w->name);
		i++;
	}
	if (p->weapons.byte_size)
		free_dynarray(&p->weapons);
}

void		free_cmp(t_env *env)
{
	(void)env;
}

void		free_custom(t_env *env)
{
	free_player(&env->player);
	if (env->custom_env.mobs.byte_size)
		free_dynarray(&env->custom_env.mobs);
	if (env->astar.d_nodes.byte_size)
		free_dynarray(&env->astar.d_nodes);
	if (env->astar.d_astar.byte_size)
		free_dynarray(&env->astar.d_astar);
	if (env->edit_env.map.meshs.byte_size)
		free_map(&env->edit_env.map);
}
