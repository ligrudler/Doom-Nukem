/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 06:34:55 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:28:59 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			load_texture(t_mlx *mlx, char *path, t_sprite *txt, bool rev)
{
	int		t;

	if (!(txt->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
												path, &txt->wdt, &txt->hgt)))
		return (-1);
	if (!(txt->img_data = mlx_get_data_addr(txt->img_ptr, &t, &t, &t)))
		return (-1);
	if (rev)
		reverse_texture(txt);
	return (0);
}

int			sample_pixel(int *img, t_point size, t_vec2d point)
{
	int		pos;

	while (point.u >= 1.0f || point.u < 0)
		point.u += (point.u >= 1.0f) ? -1.0f : 1.0f;
	while (point.v >= 1.0f || point.v < 0)
		point.v += (point.v >= 1.0f) ? -1.0f : 1.0f;
	pos = (int)(point.v * (float)size.y) * size.x;
	pos += (int)(point.u * (float)size.x);
	return (img[pos]);
}

int			shade_color(int color, float scale)
{
	unsigned char	*rgb;

	rgb = (unsigned char*)&color;
	rgb[0] *= scale;
	rgb[1] *= scale;
	rgb[2] *= scale;
	return (color);
}

void		draw_pixel(char *img, int x, int y, int color)
{
	int			pos;

	if (x < 0 || x >= WDT || y < 0 || y >= HGT)
		return ;
	pos = pixloc(x, y, false);
	*(int*)&img[pos] = color;
}
