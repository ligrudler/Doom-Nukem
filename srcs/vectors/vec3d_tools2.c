/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool		vec_outrange(t_vec3d dim, t_vec3d pos)
{
	return (pos.x < 0 || pos.x > dim.x - 1
		|| pos.y < 0 || pos.y > dim.y - 1
		|| pos.z < 0 || pos.z > dim.z - 1);
}

float		rsqrt(float number)
{
	float	i;
	float	threehalfs;
	t_rsqrt	conv;

	i = number * 0.5f;
	threehalfs = 1.5f;
	conv = (t_rsqrt){ number };
	conv.i = 0x5f3759df - (conv.i >> 1);
	conv.f *= (threehalfs - (i * conv.f * conv.f));
	return (conv.f);
}

t_vec3d		project_ortho(t_vec3d u, t_vec3d y)
{
	t_vec3d y_proj;

	if (vec_dot(u, u) == 0)
	{
		(void)y_proj;
		return (zero_vector());
	}
	else
	{
		y_proj = vec_fmult(u, (vec_dot(y, u) / vec_dot(u, u)));
		return (y_proj);
	}
}

void		vec3d_swap(t_vec3d *a, t_vec3d *b)
{
	t_vec3d		t;

	t = *a;
	*a = *b;
	*b = t;
}

t_vec3d		abs_vector(t_vec3d vec)
{
	return ((t_vec3d){fabs(vec.x), fabs(vec.y), fabs(vec.z), 0});
}
