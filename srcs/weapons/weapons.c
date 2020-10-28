/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:42:08 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/16 22:30:12 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		replace_weapons(t_env *env)
{
	int			i;

	i = 0;
	while (i < W_MAX)
	{
		env->weapons[i].w_map->spawn = env->weapons[i].start;
		i++;
	}
}

static void	switch_current_weapon(t_env *env, t_events *e)
{
	t_map	*map;
	int		nweapon;
	int		index;

	map = &env->edit_env.map;
	index = env->player.current_w;
	nweapon = env->player.weapons.nb_cells;
	if (e->buttons[BUTTON_SCROLL_UP])
	{
		index = (index >= nweapon - 1) ? 0 : index + 1;
		env->player.current_w = index;
		env->player.current = dyacc(&env->player.weapons, index);
	}
	else if (e->buttons[BUTTON_SCROLL_DOWN])
	{
		index = (index <= 0) ? nweapon - 1 : index - 1;
		env->player.current_w = index;
		env->player.current = dyacc(&env->player.weapons, index);
	}
}

static void	handle_ready(t_env *env, t_weapon *w)
{
	static float	since = 0;

	if (w->shooting > 0)
	{
		shoot_animation(env, w);
		if (w->shoot_mode == SMODE_SBS)
		{
			w->ready = false;
			return ;
		}
	}
	if (w->reloading > 0 && !(w->ready = false))
	{
		reload_animation(env, w);
		return ;
	}
	if (w->shoot_mode == SMODE_FULL_AUTO)
	{
		w->ready = (60 / since) < w->cadency;
		since = w->ready ? env->data.spent : since + env->data.spent;
	}
	else if (w->shoot_mode == SMODE_SINGLE)
		w->ready = !env->events.buttons[BUTTON_LCLIC];
	else if (w->shoot_mode == SMODE_SBS)
		w->ready = !env->events.buttons[BUTTON_LCLIC];
}

static int	weapons_events(t_env *env, t_events *e)
{
	t_weapon	*w;
	bool		r;
	bool		scroll;

	w = env->player.current;
	scroll = (e->buttons[BUTTON_SCROLL_UP] || e->buttons[BUTTON_SCROLL_DOWN]);
	if (scroll && w)
	{
		switch_current_weapon(env, &env->events);
		return (0);
	}
	r = e->keys[KEY_R];
	if (((r && w->loaded < w->magazine) || w->loaded == 0)
		&& w->ammos > 0 && w->shooting <= 0 && reload_current_weapon(env))
		return (-1);
	else if (e->buttons[BUTTON_LCLIC] && w->ready
		&& w->loaded > 0 && shoot_current_weapon(env))
		return (-1);
	handle_ready(env, w);
	return (0);
}

int			handle_weapons(t_env *env)
{
	env->player.current->shot = false;
	if (handle_sprint(env) || raster_weapon(env, env->player.current->w_map)
		|| weapons_hud(env) || weapons_events(env, &env->events))
		return (-1);
	return (0);
}
