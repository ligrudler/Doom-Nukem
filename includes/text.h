/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_H
# define TEXT_H

# define MAX_STR_CHARS 1024

# define TEXT_BOX_DIMSX 200
# define TEXT_BOX_DIMSY 30
# define TEXT_BOX_COLOR 0x333333
# define CURSOR_COLOR 0xaaaaaa

enum			e_font_id
{
	FONT_ARIAL,
	FONT_AMMOS,
	FONT_TXT_HINT,
	FONT_COOLVETICA,
	FONT_PAD,
	FONT_MAX
};

enum			e_input_fields_id
{
	FIELD_NM_MAP_WIDTH,
	FIELD_NM_MAP_HEIGHT,
	FIELD_NM_MAP_DEPTH,
	FIELD_NM_NAME,
	FIELD_MAX
};

struct			s_text_box
{
	t_dynarray		str;
	char			*name;
	t_point			o;
	t_point			b_o;
	bool			rendered;
	bool			in;
};

struct			s_kerning
{
	float	*left_pad;
	float	*right_pad;
};

struct			s_ttf_config
{
	unsigned char	s[MAX_STR_CHARS];
	int				size;
};

struct			s_ttf
{
	FT_Library	fontlib;
	FT_Face		faces[FONT_MAX - 1];
	t_kerning	kernings[FONT_MAX - 1];
	t_text_box	fields[FIELD_MAX];
};

char			*fonts_paths(unsigned int index);
int				load_fonts(t_env *env);
void			my_string_put(t_env *env, char *img, t_point o, int font);
void			textual_hint(t_env *env, char *button, char *action, int index);
int				input_fields(t_env *env, bool refresh, bool free);
t_ttf_config	*ttf_config();

void			get_glyph_pads(float *left, float *right, FT_Bitmap bmp);
int				compute_kernings(t_ttf *ttf, FT_Face face, int font);
void			map_letter(char *img, FT_Bitmap bmp, int size, t_point o);

#endif
