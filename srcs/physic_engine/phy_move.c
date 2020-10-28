/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:11:23 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 15:07:28 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static	t_vec3d	phy_handle_key(t_vec3d f, t_vec3d r, bool k[NB_KEYS])
{
	if (k[KEY_W])
	{
		f = vec_add(f, vec_fmult(f, 3.0f));
		if (k[KEY_S])
			f = zero_vector();
	}
	if (k[KEY_S])
		f = vec_add(f, vec_fmult(f, -3.0f));
	if (k[KEY_A])
		f = vec_add(f, vec_fmult(r, 3.0f));
	if (k[KEY_D])
		f = vec_add(f, vec_fmult(r, -3.0f));
	if (k[KEY_D] && k[KEY_A])
		f = zero_vector();
	if (!k[KEY_W] && !k[KEY_S] && !k[KEY_D] && !k[KEY_A])
		f = zero_vector();
	return (f);
}

static int		phy_crouch_move(t_env *e, float move, bool k)
{
	if (e->cam.stats.crouch == 0 && k)
	{
		if (move < 3.5)
			return (1);
		else
		{
			e->phy_env.crch_v = -2;
			return (0);
		}
	}
	else if (e->cam.stats.crouch == 1 && !k && e->cam.stats.onroof == 0)
	{
		if (move > 3.6)
			return (0);
		else
		{
			e->phy_env.crch_v = 2;
			return (1);
		}
	}
	else
	{
		e->phy_env.crch_v = 0;
		return (e->cam.stats.crouch);
	}
}

static	int		phy_crouch(t_env *env, bool key, t_map *maps)
{
	float move;

	move = env->cam.stats.pos.y - maps->cam_floor->a->corp.pos.y;
	if (env->cam.stats.onfloor == 1)
		return (phy_crouch_move(env, move, key));
	else
		return (0);
}

static	bool	handle_key_move(bool k[NB_KEYS])
{
	if (k[KEY_W] || k[KEY_S] || k[KEY_A] || k[KEY_D] || k[KEY_SPACE])
		return (true);
	else
		return (false);
}

void			phy_move(t_env *e, bool k[NB_KEYS], t_map *maps)
{
	t_mesh		*cam;
	t_vec3d		f;
	t_vec3d		r;

	cam = &e->edit_env.map.cam;
	e->cam.stats.speed = (k[KEY_SHIFT_LEFT]) ? 2 : 1;
	e->cam.stats.crouch = phy_crouch(e, k[KEY_CTRL_LEFT], maps);
	if (e->cam.stats.onfloor == 1 || e->cam.stats.onwall == 1)
		f = set_y_dir(e, maps);
	r = vec_fdiv((t_vec3d){f.z, 0, -f.x, 0}, e->cam.stats.aspect_ratio);
	if (handle_key_move(k) && e->cam.stats.onfloor == 1)
	{
		f = phy_handle_key(f, r, k);
		f = phy_handle_space(e, k, f);
		if (e->cam.stats.onwall == 1)
			f = test_dist_wall(e, maps->cam_wall, f);
		cam->corp.v = f;
	}
	if (k[KEY_O])
	{
		translate_mesh(maps, cam,
		vec_sub(vec_add(maps->spawn, (t_vec3d){0, 3, 0, 0}), cam->corp.pos));
		e->custom_env.spawn_jump = 5;
	}
}
