/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:44:16 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:44:17 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	maped_crosshair(t_env *env)
{
	t_point	h;
	t_point	v;
	t_point	h_d;
	t_point	v_d;

	h.x = env->data.half_wdt - CROSSHAIR_SIZE;
	h.y = env->data.half_hgt - CROSSHAIR_THICKNESS;
	v.x = env->data.half_wdt - CROSSHAIR_THICKNESS;
	v.y = env->data.half_hgt - CROSSHAIR_SIZE;
	h_d.x = CROSSHAIR_SIZE * 2;
	h_d.y = CROSSHAIR_THICKNESS * 2;
	v_d.x = CROSSHAIR_THICKNESS * 2;
	v_d.y = CROSSHAIR_SIZE * 2;
	draw_rectangle(env->mlx.img_data, h, h_d, CROSSHAIR_COLOR);
	draw_rectangle(env->mlx.img_data, v, v_d, CROSSHAIR_COLOR);
}
