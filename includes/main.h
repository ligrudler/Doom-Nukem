/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 01:37:38 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/21 14:01:06 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <time.h>
# include <math.h>
# include <limits.h>
# include <assert.h>
# include <pthread.h>
# include <ft2build.h>
# include FT_FREETYPE_H

# include "libft.h"
# include "mlx.h"
# include "errno.h"

# include "typedefs.h"
# include "vectors.h"
# include "errors.h"
# include "enemies.h"
# include "keys.h"
# include "sound.h"
# include "phy.h"
# include "sprites.h"
# include "obj_parser.h"
# include "raster.h"
# include "text.h"
# include "weapons.h"
# include "astar.h"
# include "title_screen.h"
# include "campaign.h"
# include "map_editor.h"
# include "custom.h"
# include "archive.h"
# include "hud.h"

# define NB_THREADS 8
# define WDT 1080
# define HGT 720
# define WINDOW_NAME "Doom-Nukem"

# define SENSI 0.1f
# define WALK_SPEED 0.025f
# define WSPEED 3.0f
# define PLAYER_SIZE 3.0f

enum			e_context_id
{
	C_TITLE_SCREEN,
	C_CAMPAIGN,
	C_CUSTOM,
	C_MAP_EDITOR,
	C_MAX
};

struct			s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img_ptr;
	char		*img_data;
	int			bpp;
	int			s_l;
	int			endian;
	int			pad;
};

struct			s_events
{
	bool		keys[NB_KEYS];
	bool		buttons[BUTTON_MAX];
	t_point		mouse_pos;
};

struct			s_data
{
	t_env			*env;
	struct timeval	time;
	float			spent;
	float			half_wdt;
	float			third_wdt;
	float			half_hgt;
	int				data_size;
	bool			wireframe;
};

struct			s_env
{
	t_mlx			mlx;
	t_ts_env		ts_env;
	t_camp_env		cmp_env;
	t_custom_env	custom_env;
	t_edit_env		edit_env;
	t_events		events;
	t_sound			sound;
	t_sprite		*sprites;
	t_triangle		mid;
	t_map			maps[SCENE_MAX];
	t_data			data;
	t_physics		phy_env;
	t_player		player;
	t_weapon		weapons[W_MAX];
	t_cam			cam;
	t_scroll		scroll;
	t_ttf			ttfs;
	t_pf			astar;
	t_hud			hud;
	int				context;
	int				scene;
};

double			mesure_time(bool end);
int				free_env(t_env *env);
void			free_mesh(t_mesh *m);
int				exit_doom(t_env *env, char *msg, int fd, int code);

/*
** Setup
*/
int				setup(t_env *env);
int				init_mlx(t_env *env);
void			loading_bar(unsigned int i, unsigned int max, bool last);
int				init_openal(t_sound *env);
int				load_maps(t_env *env);

/*
** MLX
*/
void			mlx_hooks(t_env *env);
int				key_press(int key, void *param);
int				key_release(int key, void *param);
int				mouse_press(int key, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_position(int x, int y, void *param);
bool			*mouse_freedom(void);
int				shade_color(int color, float scale);
int				pixloc(int x, int y, bool free);
void			draw_pixel(char *img, int x, int y, int color);
void			draw_line(t_mlx *mlx, t_point f, t_point s, int color);
int				sample_pixel(int *img, t_point size, t_vec2d point);

/*
** Contexts
*/
int				switch_context(t_env *env, unsigned int i);
void			ts_to_campaign(t_env *env);
void			ts_to_custom(t_env *env);
void			ts_to_map_editor(t_env *env);
void			campaign_to_ts(t_env *env);
void			custom_to_ts(t_env *env);
void			map_editor_to_ts(t_env *env);

/*
** Main Loop
*/
int				render(void *param);
void			test_distance_camplan(t_collide c, t_vec3d *cam_vec);

/*
** GUI
*/
int				init_scroll_file(t_env *env, char *path, char *extension);

/*
** Singletons
*/
bool			*init_parser(void);
bool			*snow_play(void);

void			free_custom(t_env *env);
void			free_cmp(t_env *env);
void			free_player(t_player *p);
void			free_fields(t_env *env);
void			free_cam(t_cam *cam);
void			free_map(t_map *map);

#endif
