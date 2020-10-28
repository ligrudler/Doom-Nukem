/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:15:58 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:29:49 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		map_sprite(char *img, t_sprite sprite, t_point o)
{
	int		x;
	int		y;
	int		k;
	int		xbound;
	int		ybound;

	xbound = o.x + sprite.wdt;
	ybound = o.y + sprite.hgt;
	k = 0;
	y = o.y;
	while (y < ybound)
	{
		x = o.x;
		while (x < xbound)
		{
			if (*(int*)(&sprite.img_data[k]) != ALPHA)
				draw_pixel(img, x, y, *(int*)(&sprite.img_data[k]));
			k += 4;
			x++;
		}
		y++;
	}
}

static void	blit_line(char *img, t_sprite sprite, t_point o, int v[2])
{
	float	sample_x;
	int		color;
	int		x;

	x = 0;
	sample_x = 0;
	while (x < v[1] - 1)
	{
		color = sample_pixel((int*)sprite.img_data,
			(t_point){sprite.wdt, sprite.hgt},
			(t_vec2d){sample_x, sprite.sample_y, 0.0f});
		if (color != ALPHA)
			draw_pixel(img, x + o.x, v[0] + o.y, color);
		sample_x += sprite.delta_x;
		x++;
	}
}

char		*blit_sprite(char *img, t_sprite sprite, t_point o, float scale)
{
	int		y;
	int		wdt;
	int		hgt;

	y = 0;
	wdt = (int)((float)sprite.wdt * scale);
	hgt = (int)((float)sprite.hgt * scale);
	sprite.delta_x = 1.0f / wdt;
	sprite.delta_y = 1.0f / hgt;
	if (wdt + o.x > WDT || hgt + o.y > HGT)
		return (img);
	sprite.sample_y = 0.0f;
	while (y < hgt)
	{
		blit_line(img, sprite, o, (int[3]){y, wdt});
		sprite.sample_y += sprite.delta_y;
		y++;
	}
	return (img);
}

t_sprite	*free_sprites(t_sprite *dest, int size)
{
	int	i;

	i = -1;
	while (dest && ++i < size)
	{
		if (dest[i].img_ptr)
			free(dest[i].img_ptr);
		if (dest[i].img_data)
			ft_strdel(&dest[i].img_data);
	}
	free(dest);
	dest = NULL;
	return (dest);
}

t_sprite	*load_sprites(t_mlx *mlx)
{
	unsigned int		i;
	int					t;
	int					error;
	t_sprite			*dest;

	error = 0;
	i = -1;
	if (!(dest = (t_sprite*)malloc(sizeof(t_sprite) * SP_MAX)))
		return (NULL);
	ft_putendl("Loading sprites...");
	while (error == 0 && ++i < SP_MAX)
	{
		loading_bar(i, SP_MAX, false);
		if (error == 0 && !(dest[i].img_ptr = mlx_xpm_file_to_image(
			mlx->mlx_ptr, sprites_paths(i), &dest[i].wdt, &dest[i].hgt)))
			error = 1;
		if (error == 0 && !(dest[i].img_data =
			mlx_get_data_addr(dest[i].img_ptr, &t, &t, &t)))
			error = 1;
		i < SP_MAX - 1 ? ft_putchar('\r') : 0;
	}
	loading_bar(i, SP_MAX, true);
	return (error ? free_sprites(dest, i) : dest);
}
