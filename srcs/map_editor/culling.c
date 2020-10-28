/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   culling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:46:33 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:46:35 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool		check_type(int type, int face)
{
	if (ft_inbounds(type, 1, 31)
		|| (ft_inbounds(type, 160, 191) && type != 163))
		return (true);
	if (ft_inbounds(type, 32, 63))
		return (face == SFACE_FRONT || face == SFACE_BOTTOM);
	else if (ft_inbounds(type, 64, 95))
		return (face == SFACE_RIGHT || face == SFACE_BOTTOM);
	else if (ft_inbounds(type, 96, 127))
		return (face == SFACE_SLOPE || face == SFACE_BOTTOM);
	else if (ft_inbounds(type, 128, 160))
		return (face == SFACE_LEFT || face == SFACE_BOTTOM);
	return (false);
}

int				check_face(t_ed_map *map, int type, int *pos, int face)
{
	if (pos[0] < 0 || pos[0] > map->width - 1
		|| pos[1] < 0 || pos[1] > map->height - 1
		|| pos[2] < 0 || pos[2] > map->depth - 1)
		return (0);
	return (check_type(map->map[pos[0]][pos[1]][pos[2]], face) ? 0 : type);
}

static void		cull_blocs(t_env *env, t_mesh *new, t_triangle *tri)
{
	int		*pos;

	pos = new->m_pos;
	if (tri->face_i == FACE_NORD)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1], pos[2] - 1 }, tri->face_i);
	else if (tri->face_i == FACE_SUD)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1], pos[2] + 1 }, tri->face_i);
	else if (tri->face_i == FACE_EST)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0] - 1, pos[1], pos[2] }, tri->face_i);
	else if (tri->face_i == FACE_OUEST)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0] + 1, pos[1], pos[2] }, tri->face_i);
	else if (tri->face_i == FACE_UP)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1] + 1, pos[2] }, tri->face_i);
	else if (tri->face_i == FACE_BOTTOM)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1] - 1, pos[2] }, tri->face_i);
}

void			culling(t_env *env, t_mesh *new, unsigned char type)
{
	int			i;
	t_triangle	*tri;

	if (type == BTXT_NONE)
		return ;
	i = -1;
	while (++i < new->tris.nb_cells)
	{
		tri = dyacc(&new->tris, i);
		if ((ft_inbounds(type, 1, 31) || ft_inbounds(type, 160, 191)))
			cull_blocs(env, new, tri);
		else
			cull_slopes(env, new, tri, type);
	}
}
