/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 05:27:06 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/12 21:16:03 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	check_place(t_point l_up, unsigned int i)
{
	if (i == TS_BUTTON_CAMPAIGN
		&& l_up.x == 415 && ft_inbounds(l_up.y, 320, 340))
		return (true);
	else if (i == TS_BUTTON_CUSTOM
		&& l_up.x == 415 && ft_inbounds(l_up.y, 410, 430))
		return (true);
	else if (i == TS_BUTTON_MAP_EDITOR
		&& l_up.x == 415 && ft_inbounds(l_up.y, 500, 520))
		return (true);
	else if (i == TS_BUTTON_QUIT
		&& l_up.x == 415 && ft_inbounds(l_up.y, 590, 610))
		return (true);
	return (false);
}

static void	cross_step(t_button *button, int i)
{
	button->l_up.y += 30;
	button->l_down.y += 30;
	button->r_up.y += 30;
	button->r_down.y += 30;
	if (check_place(button->l_up, i))
		button->in_place = true;
}

void		animation(t_env *env)
{
	static int	i = TS_BUTTON_MAX - 1;

	if (i == -1)
		return ;
	if (env->ts_env.buttons[i].in_place)
		i--;
	if (i >= 0)
		cross_step(&env->ts_env.buttons[i], i);
}
