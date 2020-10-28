/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		norme(FT_Bitmap bmp,
					unsigned int *nb, unsigned char *dst, int *x)
{
	if ((!bmp.buffer[nb[2] + *x] && !bmp.buffer[nb[2] + *x + 1]
		&& !bmp.buffer[nb[2] + *x + 2]))
	{
		*x += 3;
		nb[1] += 4;
		return (0);
	}
	dst[nb[1]] = bmp.buffer[nb[2] + *x];
	dst[nb[1] + 1] = bmp.buffer[nb[2] + *x + 1];
	dst[nb[1] + 2] = bmp.buffer[nb[2] + *x + 2];
	*x += 3;
	nb[1] += 4;
	return (1);
}

void			map_letter(char *img, FT_Bitmap bmp, int size, t_point o)
{
	int				x;
	unsigned int	nb[3];
	unsigned char	*dst;
	int				pos;

	nb[2] = 0;
	nb[0] = -1;
	if (!ft_inbounds(o.x, 0, WDT - size) || !ft_inbounds(o.y, 0, HGT - size))
		return ;
	while (++nb[0] < bmp.rows && !(x = 0))
	{
		nb[1] = 0;
		pos = ((o.y + (nb[0] - 1)) * WDT + o.x) * 4;
		if (pos < 0 && (++nb[0]))
			continue ;
		dst = (unsigned char*)&img[pos];
		while (x < bmp.pitch - 3)
			if (norme(bmp, nb, dst, &x) == 0)
				continue ;
		nb[2] += bmp.pitch;
	}
}

void			textual_hint(t_env *env, char *button, char *action, int index)
{
	t_ttf_config	*conf;
	t_point			o;
	int				x_offset;

	conf = ttf_config();
	conf->size = 20;
	ft_strcpy((char*)conf->s, "Press ");
	ft_strncat((char*)conf->s, button, 1);
	ft_strcat((char*)conf->s, " to ");
	ft_strcat((char*)conf->s, action);
	x_offset = (ft_strlen((char*)conf->s)) / 2 * conf->size;
	o.x = env->data.half_wdt - x_offset;
	o.y = HGT / 3 + (index * conf->size * 2);
	my_string_put(env, env->mlx.img_data, o, FONT_TXT_HINT);
}

int				load_fonts(t_env *env)
{
	t_ttf			*ttf;
	unsigned int	i;
	int				err;

	i = 0;
	ttf = &env->ttfs;
	if (FT_Init_FreeType(&env->ttfs.fontlib)
		&& write(2, FT_LIB, ft_strlen(FT_LIB)))
		return (-1);
	while (i < FONT_MAX - 1)
	{
		if ((err = FT_New_Face(ttf->fontlib,
			fonts_paths(i), 0, &ttf->faces[i])))
		{
			ft_putstr_fd(fonts_paths(i), 2);
			ft_putendl_fd(NSFD_ERR, 2);
			return (-1);
		}
		if (compute_kernings(ttf, ttf->faces[i], i))
			return (-1);
		i++;
	}
	return (0);
}
