/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 01:34:14 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 13:26:28 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	matrix_pointat(float m[4][4], t_vec3d pos, t_vec3d target, t_vec3d up)
{
	t_vec3d		new_f;
	t_vec3d		new_up;
	t_vec3d		new_r;
	t_vec3d		t;

	new_f = vec_sub(target, pos);
	new_f = vec_normalize(new_f);
	t = vec_fmult(new_f, vec_dot(up, new_f));
	new_up = vec_sub(up, t);
	new_r = vec_cross(new_up, new_f);
	ft_memcpy(m[0], &new_r, sizeof(t_vec3d));
	m[0][3] = -vec_dot(new_r, pos);
	ft_memcpy(m[1], &new_up, sizeof(t_vec3d));
	m[1][3] = -vec_dot(new_up, pos);
	ft_memcpy(m[2], &new_f, sizeof(t_vec3d));
	m[2][3] = -vec_dot(new_f, pos);
	ft_memcpy(m[3], &pos, sizeof(t_vec3d));
	m[3][3] = 1;
}

void	inverse_matrix(float m[4][4], float r[4][4])
{
	r[0][0] = m[0][0];
	r[0][1] = m[1][0];
	r[0][2] = m[2][0];
	r[0][3] = 0.0f;
	r[1][0] = m[0][1];
	r[1][1] = m[1][1];
	r[1][2] = m[2][1];
	r[1][3] = 0.0f;
	r[2][0] = m[0][2];
	r[2][1] = m[1][2];
	r[2][2] = m[2][2];
	r[2][3] = 0.0f;
	r[3][0] = -(m[3][0] * r[0][0] + m[3][1] * r[1][0] + m[3][2] * r[2][0]);
	r[3][1] = -(m[3][0] * r[0][1] + m[3][1] * r[1][1] + m[3][2] * r[2][1]);
	r[3][2] = -(m[3][0] * r[0][2] + m[3][1] * r[1][2] + m[3][2] * r[2][2]);
	r[3][3] = 1.0f;
}

void	translation_matrix(float m[4][4], t_vec3d v)
{
	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;
	m[3][0] = v.x;
	m[3][1] = v.y;
	m[3][2] = v.z;
}
