/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_creative_events.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:37:39 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 16:36:58 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		move(t_env *env, bool keys[NB_KEYS])
{
	t_vec3d		f;
	t_vec3d		r;

	f = vec_fmult(env->cam.stats.dir, MAPED_WALK_SPEED);
	r = (t_vec3d){f.z, 0, -f.x, f.w};
	if (keys[KEY_W])
		env->cam.stats.pos = vec_add(env->cam.stats.pos, vec_fmult(f, 3.0f));
	if (keys[KEY_S])
		env->cam.stats.pos = vec_sub(env->cam.stats.pos, vec_fmult(f, 3.0f));
	if (keys[KEY_A])
		env->cam.stats.pos = vec_add(env->cam.stats.pos, vec_fmult(r, 3.0f));
	if (keys[KEY_D])
		env->cam.stats.pos = vec_sub(env->cam.stats.pos, vec_fmult(r, 3.0f));
}

static void		switch_block_category(t_env *env, t_events *e)
{
	static bool	on = true;
	char		*bc;

	bc = &env->edit_env.current_bc;
	if (on && e->keys[KEY_DOWN])
	{
		if (*bc + 1 >= BC_MAX)
			*bc = BC_CUBE;
		else
			*bc += 1;
		env->edit_env.current_bt = *bc * 32;
		on = false;
	}
	else if (on && e->keys[KEY_UP])
	{
		if (*bc - 1 < BC_CUBE)
			*bc = BC_MAX - 1;
		else
			*bc -= 1;
		env->edit_env.current_bt = *bc * 32;
		on = false;
	}
	else if (!e->keys[KEY_DOWN] && !e->keys[KEY_UP])
		on = true;
}

static void		handle_mouse(t_env *env, t_events *e)
{
	static int	put_delay = PUT_BLOCK_DELAY;
	static int	del_delay = PUT_BLOCK_DELAY;

	if (!e->buttons[BUTTON_LCLIC])
		put_delay = 0;
	if (!e->buttons[BUTTON_RCLIC])
		del_delay = 0;
	if (e->buttons[BUTTON_LCLIC] && env->mid.mesh && put_delay <= 0
		&& (put_delay = PUT_BLOCK_DELAY))
		put_block(env);
	else if (e->buttons[BUTTON_RCLIC] && del_delay <= 0
		&& (del_delay = PUT_BLOCK_DELAY))
		del_block(env);
	put_delay--;
	del_delay--;
}

static void		handle_keys(t_env *env, t_events *e)
{
	if ((e->keys[KEY_W] || e->keys[KEY_S] || e->keys[KEY_A] || e->keys[KEY_D]))
		move(env, e->keys);
	switch_block_category(env, e);
	switch_block_type(env, e);
	replace_block(env);
}

int				handle_creative_events(t_env *env)
{
	handle_keys(env, &env->events);
	handle_mouse(env, &env->events);
	return (0);
}
