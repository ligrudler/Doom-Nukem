/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 20:34:52 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/08 20:34:54 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_rectangle(char *img, t_point o, t_point dims, int color)
{
	int		xbound;
	int		ybound;
	int		x;
	int		y;

	y = o.y;
	xbound = o.x + dims.x;
	ybound = o.y + dims.y;
	while (y < ybound)
	{
		x = o.x;
		while (x < xbound)
		{
			draw_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
