/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 21:53:49 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/08 21:55:42 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vec3d	vec_intersect_plane(t_vec3d p, t_vec3d n, t_vec3d s_e[2], float *tmp)
{
	float	plane_d;
	float	d[2];
	float	t;
	t_vec3d	l_s_end;
	t_vec3d	l_to_int;

	n = vec_normalize(n);
	plane_d = -vec_dot(n, p);
	d[0] = vec_dot(s_e[0], n);
	d[1] = vec_dot(s_e[1], n);
	t = (-plane_d - d[0]) / (d[1] - d[0]);
	*tmp = t;
	l_s_end = vec_sub(s_e[1], s_e[0]);
	l_to_int = vec_fmult(l_s_end, t);
	return (vec_add(s_e[0], l_to_int));
}

float	distance_to_plane(t_vec3d plane_n, t_vec3d plane_p, t_vec3d p)
{
	float	ret;

	plane_n = vec_normalize(plane_n);
	ret = plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z;
	ret -= vec_dot(plane_n, plane_p);
	return (ret);
}
