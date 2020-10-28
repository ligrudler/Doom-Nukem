/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		norme2(t_ttf_config *conf, int *i, t_ttf *ttf, int font)
{
	if (*i == 0 || conf->s[*i - 1] != conf->s[*i])
		if (FT_Load_Char(ttf->faces[font],
				conf->s[*i], FT_LOAD_RENDER) && ++(*i))
			return (0);
	return (1);
}

void			my_string_put(t_env *env, char *img, t_point o, int font)
{
	FT_GlyphSlot	slot;
	t_ttf_config	*c;
	t_ttf			*ttf;
	int				i;

	i = -1;
	c = ttf_config();
	ttf = &env->ttfs;
	FT_Set_Char_Size(ttf->faces[font], c->size * 96, c->size * 64, 160, 80);
	while (c->s[++i])
	{
		if (norme2(c, &i, ttf, font) == 0)
			continue ;
		slot = ttf->faces[font]->glyph;
		if (c->s[i] == 'j')
			o.x += c->size / 2;
		map_letter(img, slot->bitmap, c->size,
			(t_point){o.x + slot->bitmap_left, o.y - slot->bitmap_top});
		if (c->s[i] == ' ')
			o.x += c->size;
		else
			o.x += slot->bitmap.width
			* ttf->kernings[font].right_pad[(int)c->s[i]] + c->size / 3;
		o.y += slot->advance.y >> 6;
	}
}

static int		norme(float *left, float *right, FT_Bitmap bmp, int *nb)
{
	if (!bmp.buffer[nb[2] + nb[3]] && !bmp.buffer[nb[2] + nb[3] + 1]
		&& !bmp.buffer[nb[2] + nb[3] + 2])
	{
		nb[3] += 3;
		nb[1] += 4;
		return (0);
	}
	if ((float)(nb[3] / 3) < *left)
		*left = (float)(nb[3] / 3);
	else if ((float)(nb[3] / 3) > *right)
		*right = (float)(nb[3] / 3);
	nb[3] += 3;
	nb[1] += 4;
	return (1);
}

void			get_glyph_pads(float *left, float *right, FT_Bitmap bmp)
{
	int		nb[4];

	nb[2] = 0;
	nb[0] = -1;
	while (++nb[0] < (int)bmp.rows && !(nb[3] = 0))
	{
		nb[1] = 0;
		while (nb[3] < bmp.pitch - 3)
			if (norme(left, right, bmp, nb) == 0)
				continue ;
		nb[2] += bmp.pitch;
	}
	*right /= bmp.width;
	*left /= bmp.width;
}

int				compute_kernings(t_ttf *ttf, FT_Face face, int font)
{
	FT_GlyphSlot	slot;
	char			c;

	c = ' ';
	FT_Set_Char_Size(face, 50 * 96, 50 * 64, 160, 80);
	if (!(ttf->kernings[font].left_pad = (float*)malloc(sizeof(float) * 127))
	|| !(ttf->kernings[font].right_pad = (float*)malloc(sizeof(float) * 127)))
		return (-1);
	while (c < 127)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER) && ++c)
			continue ;
		slot = face->glyph;
		ttf->kernings[font].left_pad[(int)c] = INFINITY;
		ttf->kernings[font].right_pad[(int)c] = -INFINITY;
		get_glyph_pads(&ttf->kernings[font].left_pad[(int)c],
			&ttf->kernings[font].right_pad[(int)c], slot->bitmap);
		c++;
	}
	return (0);
}
