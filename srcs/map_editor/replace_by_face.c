/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_by_face.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:41:06 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 17:41:07 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	replace_by_ouest_slope(t_env *env, int *pos, char face)
{
	if (face == SFACE_SLOPE)
		return (1);
	else if (face == SFACE_LEFT)
		pos[2]--;
	else if (face == SFACE_RIGHT)
		pos[2]++;
	else if (face == SFACE_FRONT)
		pos[0]++;
	else if (face == SFACE_BOTTOM)
		pos[1]--;
	if (!ft_inbounds(pos[0], 0, env->edit_env.new_map.width - 1)
			|| !ft_inbounds(pos[1], 0, env->edit_env.new_map.height - 1)
			|| !ft_inbounds(pos[2], 0, env->edit_env.new_map.depth - 1))
		return (1);
	return (0);
}

static int	replace_by_est_slope(t_env *env, int *pos, char face)
{
	if (face == SFACE_SLOPE)
		return (1);
	else if (face == SFACE_LEFT)
		pos[2]++;
	else if (face == SFACE_RIGHT)
		pos[2]--;
	else if (face == SFACE_FRONT)
		pos[0]--;
	else if (face == SFACE_BOTTOM)
		pos[1]--;
	if (!ft_inbounds(pos[0], 0, env->edit_env.new_map.width - 1)
			|| !ft_inbounds(pos[1], 0, env->edit_env.new_map.height - 1)
			|| !ft_inbounds(pos[2], 0, env->edit_env.new_map.depth - 1))
		return (1);
	return (0);
}

static int	replace_by_sud_slope(t_env *env, int *pos, char face)
{
	if (face == SFACE_SLOPE)
		return (1);
	else if (face == SFACE_LEFT)
		pos[0]--;
	else if (face == SFACE_RIGHT)
		pos[0]++;
	else if (face == SFACE_FRONT)
		pos[2]--;
	else if (face == SFACE_BOTTOM)
		pos[1]--;
	if (!ft_inbounds(pos[0], 0, env->edit_env.new_map.width - 1)
			|| !ft_inbounds(pos[1], 0, env->edit_env.new_map.height - 1)
			|| !ft_inbounds(pos[2], 0, env->edit_env.new_map.depth - 1))
		return (1);
	return (0);
}

static int	replace_by_nord_slope(t_env *env, int *pos, char face)
{
	if (face == SFACE_SLOPE)
		return (1);
	else if (face == SFACE_LEFT)
		pos[0]++;
	else if (face == SFACE_RIGHT)
		pos[0]--;
	else if (face == SFACE_FRONT)
		pos[2]++;
	else if (face == SFACE_BOTTOM)
		pos[1]--;
	if (!ft_inbounds(pos[0], 0, env->edit_env.new_map.width - 1)
			|| !ft_inbounds(pos[1], 0, env->edit_env.new_map.height - 1)
			|| !ft_inbounds(pos[2], 0, env->edit_env.new_map.depth - 1))
		return (1);
	return (0);
}

int			replace_by_face(t_env *env, int *pos, char face, unsigned char type)
{
	if (ft_inbounds(type, 32, 63))
		return (replace_by_est_slope(env, pos, face));
	else if (ft_inbounds(type, 64, 95))
		return (replace_by_ouest_slope(env, pos, face));
	else if (ft_inbounds(type, 96, 127))
		return (replace_by_nord_slope(env, pos, face));
	else if (ft_inbounds(type, 128, 160))
		return (replace_by_sud_slope(env, pos, face));
	if (face == FACE_OUEST)
		pos[0]++;
	else if (face == FACE_EST)
		pos[0]--;
	else if (face == FACE_UP)
		pos[1]++;
	else if (face == FACE_BOTTOM)
		pos[1]--;
	else if (face == FACE_NORD)
		pos[2]--;
	else if (face == FACE_SUD)
		pos[2]++;
	if (!ft_inbounds(pos[0], 0, env->edit_env.new_map.width - 1)
			|| !ft_inbounds(pos[1], 0, env->edit_env.new_map.height - 1)
			|| !ft_inbounds(pos[2], 0, env->edit_env.new_map.depth - 1))
		return (1);
	return (0);
}
