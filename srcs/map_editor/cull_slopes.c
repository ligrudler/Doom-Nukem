/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cull_slopes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:45:09 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:45:10 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		east_slope(t_env *env, t_mesh *new, t_triangle *tri)
{
	int		*pos;

	pos = new->m_pos;
	if (tri->face_i == SFACE_LEFT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1], pos[2] + 1 }, tri->face_i);
	else if (tri->face_i == SFACE_RIGHT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1], pos[2] - 1 }, tri->face_i);
	else if (tri->face_i == SFACE_FRONT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0] - 1, pos[1], pos[2] }, tri->face_i);
	else if (tri->face_i == SFACE_BOTTOM)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1] - 1, pos[2] }, tri->face_i);
}

static void		west_slope(t_env *env, t_mesh *new, t_triangle *tri)
{
	int		*pos;

	pos = new->m_pos;
	if (tri->face_i == SFACE_LEFT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1], pos[2] - 1 }, tri->face_i);
	else if (tri->face_i == SFACE_RIGHT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1], pos[2] + 1 }, tri->face_i);
	else if (tri->face_i == SFACE_FRONT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0] + 1, pos[1], pos[2] }, tri->face_i);
	else if (tri->face_i == SFACE_BOTTOM)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1] - 1, pos[2] }, tri->face_i);
}

static void		north_slope(t_env *env, t_mesh *new, t_triangle *tri)
{
	int		*pos;

	pos = new->m_pos;
	if (tri->face_i == SFACE_LEFT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0] + 1, pos[1], pos[2] }, tri->face_i);
	else if (tri->face_i == SFACE_RIGHT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0] - 1, pos[1], pos[2] }, tri->face_i);
	else if (tri->face_i == SFACE_FRONT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1], pos[2] + 1 }, tri->face_i);
	else if (tri->face_i == SFACE_BOTTOM)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1] - 1, pos[2] }, tri->face_i);
}

static void		south_slope(t_env *env, t_mesh *new, t_triangle *tri)
{
	int		*pos;

	pos = new->m_pos;
	if (tri->face_i == SFACE_LEFT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0] - 1, pos[1], pos[2] }, tri->face_i);
	else if (tri->face_i == SFACE_RIGHT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0] + 1, pos[1], pos[2] }, tri->face_i);
	else if (tri->face_i == SFACE_FRONT)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1], pos[2] - 1 }, tri->face_i);
	else if (tri->face_i == SFACE_BOTTOM)
		tri->sp = check_face(&env->edit_env.new_map, new->type,
			(int[3]){ pos[0], pos[1] - 1, pos[2] }, tri->face_i);
}

void			cull_slopes(t_env *env, t_mesh *new, t_triangle *tri, int type)
{
	if (ft_inbounds(type, 32, 63))
		east_slope(env, new, tri);
	else if (ft_inbounds(type, 64, 95))
		west_slope(env, new, tri);
	else if (ft_inbounds(type, 96, 127))
		north_slope(env, new, tri);
	else if (ft_inbounds(type, 128, 160))
		south_slope(env, new, tri);
}
