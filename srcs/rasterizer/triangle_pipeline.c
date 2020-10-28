/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 00:13:54 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 13:37:33 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	scale_to_screen(t_env *env, t_triangle *t)
{
	t_vec3d		scale;
	t_vec3d		pad;

	pad = (t_vec3d){1.0f, 1.0f, 0.0f, 0.0f};
	scale = (t_vec3d){env->data.half_wdt, env->data.half_hgt, 1.0f, 1.0f};
	t->points[0] = vec_add(t->points[0], pad);
	t->points[1] = vec_add(t->points[1], pad);
	t->points[2] = vec_add(t->points[2], pad);
	t->points[0] = vec_mult(t->points[0], scale);
	t->points[1] = vec_mult(t->points[1], scale);
	t->points[2] = vec_mult(t->points[2], scale);
}

static void	get_txt_vectors(t_triangle *t, t_triangle clipped)
{
	t->txt[0] = clipped.txt[0];
	t->txt[1] = clipped.txt[1];
	t->txt[2] = clipped.txt[2];
	t->txt[0].u /= t->points[0].w;
	t->txt[1].u /= t->points[1].w;
	t->txt[2].u /= t->points[2].w;
	t->txt[0].v /= t->points[0].w;
	t->txt[1].v /= t->points[1].w;
	t->txt[2].v /= t->points[2].w;
	t->txt[0].w = 1.0f / t->points[0].w;
	t->txt[1].w = 1.0f / t->points[1].w;
	t->txt[2].w = 1.0f / t->points[2].w;
}

static int	project_triangle(t_env *env, t_triangle *t, t_triangle clipped,
															t_dynarray *tris)
{
	t->points[0] = multiply_matrix(env->cam.p_m, clipped.points[0]);
	t->points[1] = multiply_matrix(env->cam.p_m, clipped.points[1]);
	t->points[2] = multiply_matrix(env->cam.p_m, clipped.points[2]);
	get_txt_vectors(t, clipped);
	t->points[0] = vec_fdiv(t->points[0], t->points[0].w);
	t->points[1] = vec_fdiv(t->points[1], t->points[1].w);
	t->points[2] = vec_fdiv(t->points[2], t->points[2].w);
	scale_to_screen(env, t);
	t->color = clipped.color;
	t->textured = clipped.textured;
	t->voxel = clipped.voxel;
	t->sp = clipped.sp;
	t->mesh = clipped.mesh;
	if (push_dynarray(tris, t, false))
		return (-1);
	return (0);
}

static int	clip_near_plane(t_env *env, t_triangle t, t_vec3d normal,
															t_dynarray *tris)
{
	t_triangle	clipped[2];
	float		illum;
	int			nclip;
	int			i;

	i = 0;
	illum = vec_dot(normal, env->cam.light);
	t.scale = (illum + 1.0f) / 2.0f;
	t.color = shade_color(t.color, t.scale);
	t.normal = normal;
	t.points[0] = multiply_matrix(env->cam.v_m, t.points[0]);
	t.points[1] = multiply_matrix(env->cam.v_m, t.points[1]);
	t.points[2] = multiply_matrix(env->cam.v_m, t.points[2]);
	nclip = clip_triangle((t_vec3d){0.0f, 0.0f, 0.1f, 1.0f},
		(t_vec3d){0.0f, 0.0f, 1.0f, 1.0f}, t, clipped);
	while (i < nclip)
	{
		if (project_triangle(env, &t, clipped[i], tris))
			return (-1);
		i++;
	}
	return (0);
}

int			triangle_pipeline(t_env *env, t_triangle *t, t_dynarray *tris,
																	t_mesh *m)
{
	t_vec3d		normal;
	t_vec3d		line1;
	t_vec3d		line2;

	if (t->voxel && t->sp == BTXT_NONE)
		return (0);
	t->points[0] = matrix_mult_vec(env->cam.w_m, t->points[0]);
	t->points[1] = matrix_mult_vec(env->cam.w_m, t->points[1]);
	t->points[2] = matrix_mult_vec(env->cam.w_m, t->points[2]);
	line1 = vec_sub(t->points[1], t->points[0]);
	line2 = vec_sub(t->points[2], t->points[0]);
	normal = vec_cross(line1, line2);
	normal = vec_normalize(normal);
	m->corp.norm = normal;
	if (vec_dot(normal, vec_sub(t->points[0], env->cam.stats.pos)) < 0.0f)
	{
		if (clip_near_plane(env, *t, normal, tris))
			return (-1);
	}
	return (0);
}
