/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 00:21:40 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 15:17:03 by grudler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef struct s_mlx			t_mlx;
typedef struct s_sprite			t_sprite;

typedef struct s_events			t_events;

typedef struct s_data			t_data;

typedef struct s_env			t_env;

typedef struct s_face			t_face;
typedef struct s_mtl			t_mtl;
typedef struct s_map			t_map;
typedef struct s_parser			t_parser;

typedef struct s_point			t_point;
typedef struct s_vec2d			t_vec2d;
typedef struct s_vec3d			t_vec3d;
typedef struct s_triangle		t_triangle;
typedef struct s_mesh			t_mesh;
typedef struct s_filler			t_filler;
typedef struct s_texturizer		t_texturizer;
typedef struct s_clipper		t_clipper;
typedef struct s_rasthread		t_rasthread;
typedef struct s_cam_stats		t_cam_stats;
typedef struct s_cam			t_cam;

typedef struct s_sample			t_sample;
typedef struct s_sound			t_sound;

typedef struct s_button			t_button;
typedef struct s_ts_env			t_ts_env;
typedef struct s_custom_env		t_custom_env;

typedef struct s_box			t_box;
typedef struct s_collide		t_collide;
typedef struct s_corp			t_corp;
typedef struct s_physics		t_physics;

typedef	struct s_camp_env		t_camp_env;
typedef struct s_door			t_door;
typedef struct s_custom_door	t_custom_door;

typedef	struct s_edit_env		t_edit_env;

typedef struct s_player			t_player;
typedef struct s_sector			t_sector;

typedef struct s_ttf			t_ttf;
typedef struct s_ttf_config		t_ttf_config;

typedef struct s_weapon			t_weapon;
typedef struct s_enemy			t_enemy;
typedef struct s_loot			t_loot;

typedef struct s_ed_map			t_ed_map;
typedef struct s_scroll			t_scroll;
typedef struct s_custom_game	t_custom_game;
typedef struct s_go_env			t_go_env;

typedef struct s_kerning		t_kerning;
typedef struct s_text_box		t_text_box;
typedef struct s_cube_pallet	t_cube_pallet;

typedef struct s_node			t_node;
typedef struct s_pathfinding	t_pf;
typedef struct s_event_block	t_event_block;
typedef union u_bep				t_bep;

typedef struct s_hud			t_hud;
typedef struct s_buzzer			t_buzzer;

#endif
