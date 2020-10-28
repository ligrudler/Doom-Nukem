/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/21 15:03:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# define ALPHA -16777216

# define BLACK "\033[22;30m"
# define BLUE "\033[22;34m"
# define RED "\033[22;31m"
# define L_RED "\033[01;31m"
# define L_GREEN "\033[01;32m"
# define GRA "\033[1m"
# define STOP "\033[0m"

enum		e_sprite_id
{
	SP_TS_BUTTON_1C,
	SP_TS_BUTTON_1H,
	SP_TS_BUTTON_1O,
	SP_TS_BUTTON_2C,
	SP_TS_BUTTON_2H,
	SP_TS_BUTTON_2O,
	SP_TS_BUTTON_3C,
	SP_TS_BUTTON_3H,
	SP_TS_BUTTON_3O,
	SP_TS_BUTTON_5C,
	SP_TS_BUTTON_5H,
	SP_TS_BUTTON_5O,
	SP_TS_LOGO,
	SP_CP_BUTTON_1C,
	SP_CP_BUTTON_1H,
	SP_CP_BUTTON_1O,
	SP_CP_BUTTON_2C,
	SP_CP_BUTTON_2H,
	SP_CP_BUTTON_2O,
	SP_ME_BUTTON_2C,
	SP_ME_BUTTON_2H,
	SP_ME_BUTTON_2O,
	SP_ME_BUTTON_CREATE_1C,
	SP_ME_BUTTON_CREATE_1H,
	SP_ME_BUTTON_CREATE_1O,
	SP_NM_BUTTON_MAPED_2C,
	SP_NM_BUTTON_MAPED_2O,
	SP_NM_BUTTON_MAPED_2H,
	SP_TS_BACKGROUND,
	SP_CMP_TS_BACKGROUND,
	SP_ME_BACKGROUND,
	SP_ME_NEW_MAP_BACKGROUND,
	SP_ME_MENU_TITLE,
	SP_ME_NM_TITLE,
	SP_CUSTOM_BACKGROUND,
	SP_HITMARKER,
	SP_GAME_OVER,
	SP_YES_OFF,
	SP_YES_HOVER,
	SP_YES_ON,
	SP_NO_OFF,
	SP_NO_HOVER,
	SP_NO_ON,
	SP_COIN,
	SP_NEW_WAVE,
	SP_CMP_KEY,
	SP_CMP_1,
	SP_CMP_2,
	SP_CMP_3,
	SP_CMP_4,
	SP_CMP_5,
	SP_CMP_6,
	SP_CMP_7,
	SP_CMP_8,
	SP_CMP_GAME_OVER,
	SP_CMP_VICTORY,
	SP_MAX
};

struct		s_sprite
{
	void			*img_ptr;
	char			*img_data;
	int				hgt;
	int				wdt;
	float			delta_x;
	float			delta_y;
	float			sample_y;
	int				alpha;
	int				pad;
};

char		*sprites_paths(unsigned int index);
char		*blit_sprite(char *img, t_sprite sprite, t_point o, float scale);
void		map_sprite(char *img, t_sprite sprite, t_point o);
int			crop_sprite(t_env *env,
				t_sprite base, t_sprite *crop, t_vec2d csize[2]);
t_sprite	*load_sprites(t_mlx *mlx);
int			load_texture(t_mlx *mlx, char *path, t_sprite *txt, bool rev);
void		reverse_texture(t_sprite *txt);

#endif
