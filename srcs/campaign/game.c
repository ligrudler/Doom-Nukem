/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:32:00 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:32:40 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	move(t_env *env, bool keys[NB_KEYS])
{
	float		coeff;
	t_vec3d		f;
	t_vec3d		r;

	coeff = WALK_SPEED;
	env->cam.stats.acc = env->cam.stats.pos;
	if (env->cmp_env.sector == SECTOR_START_ROOM)
		coeff *= 2;
	coeff *= (env->events.keys[KEY_SHIFT_LEFT]) ? 2 : 1;
	f = vec_fmult(env->cam.stats.dir, coeff);
	r = (t_vec3d){f.z, 0, -f.x, f.w};
	if (keys[KEY_W])
		env->cam.stats.pos = vec_add(env->cam.stats.pos, vec_fmult(f, 3.0f));
	if (keys[KEY_S])
		env->cam.stats.pos = vec_sub(env->cam.stats.pos, vec_fmult(f, 3.0f));
	if (keys[KEY_A])
		env->cam.stats.pos = vec_add(env->cam.stats.pos, vec_fmult(r, 3.0f));
	if (keys[KEY_D])
		env->cam.stats.pos = vec_sub(env->cam.stats.pos, vec_fmult(r, 3.0f));
	if (keys[KEY_H])
	{
		env->cmp_env.sector = SECTOR_START_ROOM;
		env->cmp_env.hint_t = 2;
	}
	env->cam.stats.acc = vec_sub(env->cam.stats.acc, env->cam.stats.pos);
}

static int	beep_bomb(t_env *env)
{
	static float	left = 0;

	if (left <= 0)
	{
		if (sound_system(env, SA_CMP_BEEP,
			sp_fork(env->sound.volume, 1, env->cam.stats.pos)))
			return (-1);
		left = env->cmp_env.countdown / 10;
	}
	left -= env->data.spent;
	return (0);
}

static int	handle_door(t_env *env)
{
	if (env->cmp_env.sector != SECTOR_START_ROOM)
	{
		if (env->cmp_env.hint_t > 0)
			textual_hint(env, "H", "come back to hub", 0);
		env->cmp_env.hint_t -= env->data.spent;
		return (0);
	}
	if (vec3d_dist(env->cam.stats.pos, env->cmp_env.door) < 2)
	{
		textual_hint(env, "E", "open the door", 0);
		if (env->events.keys[KEY_E])
		{
			if (sound_system(env, SA_CMP_DOOR,
				sp_fork(env->sound.volume * 2, 1, env->cmp_env.door)))
				return (-1);
			env->cmp_env.sector = SECTOR_DUST;
		}
	}
	return (0);
}

static int	handle_end(t_env *env)
{
	env->cmp_env.failed = (env->cmp_env.countdown <= 0);
	if (env->cmp_env.done)
		env->cmp_env.sector = SECTOR_START_ROOM;
	if (env->cmp_env.done || env->cmp_env.failed)
	{
		if (env->cmp_env.failed && sound_system(env, SA_CMP_BOOM,
			sp_fork(env->sound.volume, 1, env->cam.stats.pos)))
			return (-1);
		if (switch_campaign_subcontext(env, CMP_SC_END))
			return (-1);
	}
	return (0);
}

int			cmp_game(t_env *env)
{
	t_camp_env	*cmp_env;

	cmp_env = &env->cmp_env;
	if (sound_manager(env, SA_GAME1))
		return (-1);
	env->scene = cmp_env->sectors[cmp_env->sector].map;
	move(env, env->events.keys);
	camera_aim(env);
	clear_screen_buffers(env);
	if (rasterizer(env, &env->maps[env->scene], false)
		|| handle_countdown(env, (t_point){485, 50})
		|| handle_switches(env)
		|| beep_bomb(env))
		return (-1);
	handle_enigma(env);
	handle_door(env);
	handle_end(env);
	mlx_put_image_to_window(env->mlx.mlx_ptr,
		env->mlx.mlx_win, env->mlx.img_ptr, 0, 0);
	return (0);
}
