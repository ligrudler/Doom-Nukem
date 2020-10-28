/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:14:55 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 13:15:57 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vec3d		multiply_matrix(float m[4][4], t_vec3d o)
{
	t_vec3d			ret;

	ret.x = o.x * m[0][0] + o.y * m[1][0] + o.z * m[2][0] + m[3][0];
	ret.y = o.x * m[0][1] + o.y * m[1][1] + o.z * m[2][1] + m[3][1];
	ret.z = o.x * m[0][2] + o.y * m[1][2] + o.z * m[2][2] + m[3][2];
	ret.w = o.x * m[0][3] + o.y * m[1][3] + o.z * m[2][3] + m[3][3];
	return (ret);
}

void		matrix_mult_matrix(float m1[4][4], float m2[4][4], float ret[4][4])
{
	unsigned int	c;
	unsigned int	r;
	float			tmp;

	c = 0;
	while (c < 4)
	{
		r = 0;
		while (r < 4)
		{
			tmp = m1[r][0] * m2[0][c] + m1[r][1] * m2[1][c];
			tmp += m1[r][2] * m2[2][c] + m1[r][3] * m2[3][c];
			ret[r][c] = tmp;
			r++;
		}
		c++;
	}
}

t_vec3d		matrix_mult_vec(float m[4][4], t_vec3d i)
{
	t_vec3d v;

	v.x = i.x * m[0][0] + i.y * m[1][0] + i.z * m[2][0] + i.w * m[3][0];
	v.y = i.x * m[0][1] + i.y * m[1][1] + i.z * m[2][1] + i.w * m[3][1];
	v.z = i.x * m[0][2] + i.y * m[1][2] + i.z * m[2][2] + i.w * m[3][2];
	v.w = i.x * m[0][3] + i.y * m[1][3] + i.z * m[2][3] + i.w * m[3][3];
	return (v);
}
