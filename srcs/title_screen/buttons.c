/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 04:02:00 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/21 19:14:44 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_button(t_button *button, t_point o, t_sprite *sp[3])
{
	if (!sp || !sp[0] || !sp[1] || !sp[2])
		return ;
	button->l_up.x = o.x;
	button->l_up.y = o.y;
	button->r_up.x = o.x + sp[0]->wdt;
	button->r_up.y = o.y;
	button->l_down.x = o.x;
	button->l_down.y = o.y + sp[0]->hgt;
	button->r_down.x = o.x + sp[0]->wdt;
	button->r_down.y = o.y + sp[0]->hgt;
	button->on = sp[0];
	button->hover = sp[1];
	button->off = sp[2];
	button->is_hover = false;
}

bool	is_on_button(t_point mouse, t_button button)
{
	if (mouse.x >= button.l_up.x && mouse.x <= button.r_up.x
		&& mouse.y >= button.r_up.y && mouse.y <= button.r_down.y)
		return (true);
	return (false);
}

void	render_button(t_env *env, t_button button)
{
	t_sprite	*sprite;
	t_point		pos;
	bool		clic;

	pos = (t_point){button.l_up.x, button.l_up.y};
	clic = false;
	if (button.is_hover)
	{
		if (env->events.buttons[BUTTON_LCLIC])
		{
			sprite = button.on;
			map_sprite(env->mlx.img_data, *sprite, pos);
			clic = true;
		}
		else
			sprite = button.hover;
	}
	else
		sprite = button.off;
	if (!clic)
		map_sprite(env->mlx.img_data, *sprite, pos);
}
