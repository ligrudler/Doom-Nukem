/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:11:32 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/18 20:11:33 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_vec3d	look_for_slope_vect(t_triangle *tri, t_vec3d *dir)
{
	t_vec3d u;
	t_vec3d v;
	t_vec3d w;

	u = vec_sub(tri->points[0], tri->points[1]);
	if (vec_dot(u, *dir) < 0)
		return ((t_vec3d){-u.x, -u.y, -u.z, -u.w});
	v = vec_sub(tri->points[1], tri->points[2]);
	if (vec_dot(v, *dir) < 0)
		return ((t_vec3d){-v.x, -v.y, -v.z, -v.w});
	w = vec_sub(tri->points[2], tri->points[0]);
	if (vec_dot(w, *dir) < 0)
		return ((t_vec3d){-v.x, -v.y, -v.z, -v.w});
	return (zero_vector());
}

static	t_vec3d	*coefdir_plan(t_env *env, t_mesh *m, t_mesh *cam, t_vec3d *dir)
{
	t_vec3d w;
	t_vec3d	*new_dir;
	t_vec3d step_dir;

	(void)cam;
	w = (t_vec3d){2, 0, 2, 0};
	if (m->tris.nb_cells == 8 && env->cam.stats.onfloor == 1)
		w = look_for_slope_vect(dyacc(&m->tris, 4), dir);
	new_dir = dir;
	step_dir = project_ortho(w, *dir);
	new_dir->y = step_dir.y;
	return (new_dir);
}

t_vec3d			set_y_dir(t_env *env, t_map *map)
{
	t_vec3d	f;
	t_mesh	*a;
	t_mesh	*cam;

	f = (t_vec3d){2, 0, 2, 0};
	if (env->cam.stats.onwall == 0)
	{
		a = map->cam_floor->a;
		cam = map->cam_floor->b;
		f = vec_fmult(*coefdir_plan(env, a, cam, &env->cam.stats.dir),
		MAPED_WALK_SPEED * env->cam.stats.speed);
	}
	else if (env->cam.stats.onwall == 1)
	{
		a = map->cam_wall->a;
		cam = map->cam_wall->b;
		f = vec_fmult(*coefdir_plan(env, a, cam, &env->cam.stats.dir),
		MAPED_WALK_SPEED * env->cam.stats.speed);
	}
	return (f);
}

t_vec3d			test_dist_wall(t_env *env, t_collide *c, t_vec3d f)
{
	t_mesh	*cam;
	t_mesh	*wall;
	t_vec3d	vec;
	t_vec3d	vec2;

	cam = c->b;
	wall = c->a;
	vec = vec_sub(wall->corp.pos, cam->corp.pos);
	vec2 = (t_vec3d){vec.x, 0, vec.z, 0};
	f = vec_fmult(f, 0.5);
	if (wall->tris.nb_cells > 8 && vec_dot(f, vec2) > 0
			&& vec_norm(vec2) < 3)
		f = zero_vector();
	if (wall->tris.nb_cells == 8)
		f = *coefdir_plan(env, c->a, c->b, &f);
	return (f);
}
