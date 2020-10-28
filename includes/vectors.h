/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

struct			s_vec2d
{
	float		u;
	float		v;
	float		w;
};

struct			s_vec3d
{
	float		x;
	float		y;
	float		z;
	float		w;
};

typedef union	u_rsqrt
{
	float		f;
	uint32_t	i;
}				t_rsqrt;

float			rsqrt(float number);

bool			vec_outrange(t_vec3d dim, t_vec3d pos);

t_vec3d			vec_add(t_vec3d a, t_vec3d b);
t_vec3d			vec_sub(t_vec3d a, t_vec3d b);
t_vec3d			vec_mult(t_vec3d a, t_vec3d b);
t_vec3d			vec_div(t_vec3d a, t_vec3d b);
t_vec3d			vec_relu(t_vec3d v);

t_vec3d			vec_fdiv(t_vec3d a, float n);
t_vec3d			vec_fmult(t_vec3d a, float n);
t_vec3d			vec_fsub(t_vec3d a, float n);

t_vec3d			zero_vector();

void			vec3d_swap(t_vec3d *a, t_vec3d *b);
t_vec3d			vec_cross(t_vec3d a, t_vec3d b);
t_vec3d			vec_normalize(t_vec3d vec);
float			vec_norm(t_vec3d vec);
float			vec_dot(t_vec3d a, t_vec3d b);

float			vec3d_dist(t_vec3d o, t_vec3d v);

t_vec3d			vec_intersect_plane(t_vec3d plane_p, t_vec3d plane_n,
										t_vec3d s_e[2], float *tmp);
float			distance_to_plane(t_vec3d plane_n, t_vec3d plane_p, t_vec3d p);

void			vec2d_swap(t_vec2d *a, t_vec2d *b);
t_vec3d			project_ortho(t_vec3d u, t_vec3d y);
t_vec3d			abs_vector(t_vec3d vec);
#endif
