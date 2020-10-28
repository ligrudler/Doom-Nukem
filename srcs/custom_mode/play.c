/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:00:32 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 15:09:40 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	handle_move_keys(t_env *env, bool k[NB_KEYS], t_vec3d f, t_vec3d r)
{
	t_map		*map;

	map = &env->edit_env.map;
	if (k[KEY_W])
	{
		env->cam.stats.pos = vec_add(env->cam.stats.pos, vec_fmult(f, WSPEED));
		translate_mesh(map, &map->cam, vec_fmult(f, WSPEED));
	}
	if (k[KEY_A])
	{
		env->cam.stats.pos = vec_add(env->cam.stats.pos, vec_fmult(r, WSPEED));
		translate_mesh(map, &map->cam, vec_fmult(r, WSPEED));
	}
	if (k[KEY_S])
	{
		env->cam.stats.pos = vec_sub(env->cam.stats.pos, vec_fmult(f, WSPEED));
		translate_mesh(map, &map->cam, vec_fmult(f, -WSPEED));
	}
	if (k[KEY_D])
	{
		env->cam.stats.pos = vec_sub(env->cam.stats.pos, vec_fmult(r, WSPEED));
		translate_mesh(map, &map->cam, vec_fmult(r, -WSPEED));
	}
}

static void	move(t_env *env, bool keys[NB_KEYS])
{
	t_vec3d		f;
	t_vec3d		r;

	f = vec_fmult(env->cam.stats.dir, MAPED_WALK_SPEED);
	r = (t_vec3d){f.z, 0, -f.x, f.w};
	handle_move_keys(env, keys, f, r);
}

static void	ft_type_move(t_env *env, bool keys[NB_KEYS], t_map *maps)
{
	if (env->phy_env.type_move == false)
		move(env, keys);
	else
		phy_move(env, keys, maps);
}

static int	handle_keys(t_env *env, t_events *e)
{
	if (e->keys[KEY_T])
	{
		env->phy_env.type_move = false;
		env->hud.timephysic = env->data.time.tv_sec;
	}
	if (e->keys[KEY_Y])
	{
		env->phy_env.type_move = true;
		env->hud.timephysic = env->data.time.tv_sec;
	}
	if (e->keys[KEY_M])
		if (switch_custom_context(env, CUSTOM_SC_MENU))
			return (-1);
	ft_type_move(env, e->keys, &env->edit_env.map);
	return (0);
}

int			custom_play(t_env *env)
{
	if (sound_manager(env, SA_MAX))
		return (-1);
	handle_waves(env);
	camera_aim(env);
	if (env->phy_env.type_move && physic_engine(env, &env->edit_env.map))
		return (-1);
	clear_screen_buffers(env);
	if (rasterizer(env, &env->edit_env.map, false))
		return (-1);
	handle_moon(env);
	if (handle_loots(env) || handle_weapons(env) || handle_block_events(env)
		|| draw_hud(env))
		return (-1);
	if (handle_keys(env, &env->events)
		|| handle_player(env) || handle_enemies(env))
		return (-1);
	mlx_put_image_to_window(env->mlx.mlx_ptr,
		env->mlx.mlx_win, env->mlx.img_ptr, 0, 0);
	return (0);
}
