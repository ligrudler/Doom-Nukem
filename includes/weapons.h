/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:37:41 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 15:39:22 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPONS_H
# define WEAPONS_H

# define ACC_START 24
# define ACC_SPREAD 0.6f
# define AMMO_FONT_SIZE 24
# define W_NAME_FONT_SIZE 16
# define W_SHAKE 12

# define RELOAD_TIME 2.5f
# define RELOAD_SPEED 0.05f
# define HITMARKER_T 5

enum	e_weapons
{
	W_FAMAS,
	W_AK47,
	W_SAWED_OFF,
	W_GLOCK_18,
	W_AUG,
	W_UMP45,
	W_MAG7,
	W_GALIL,
	W_NEGEV,
	W_TEC9,
	W_MAX
};

enum	e_shoot_mode
{
	SMODE_SBS,
	SMODE_SINGLE,
	SMODE_FULL_AUTO,
	SMODE_MAX
};

struct	s_weapon
{
	t_vec3d		start;
	t_map		*w_map;
	t_mesh		*mesh;
	t_mesh		*breech;
	char		*name;
	float		accuracy;
	int			shoot;
	int			reload;
	int			reticle;
	int			damages;
	int			magazine;
	int			loaded;
	int			ammos;
	int			max_ammos;
	int			cadency;
	int			index;
	float		reloading;
	float		shooting;
	float		recoil;
	bool		ready;
	bool		shot;
	char		shoot_mode;
};

int		init_weapons(t_env *env);
void	replace_weapons(t_env *env);

int		handle_sprint(t_env *env);
int		shoot_current_weapon(t_env *env);
void	shoot_animation(t_env *env, t_weapon *w);
int		reload_current_weapon(t_env *env);
void	reload_animation(t_env *env, t_weapon *w);
int		add_random_weapon(t_env *env);

int		handle_weapons(t_env *env);
void	draw_reticule(t_env *env);
int		print_ammos(t_env *env, t_weapon *w);
int		weapons_hud(t_env *env);
void	assign_weapons_stats(t_env *env);
void	assign_meshs(t_mesh *m);

#endif
