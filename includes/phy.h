/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebosson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by bebosson          #+#    #+#             */
/*   Updated: 2020/07/18 20:09:55 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHY_H
# define PHY_H

struct	s_corp
{
	t_vec3d		acc;
	t_vec3d		vo;
	t_vec3d		v;
	t_vec3d		v_cpy;
	t_vec3d		pos;
	t_vec3d		o;
	t_vec3d		norm;
	t_vec3d		dims;
};

struct	s_collide
{
	t_mesh			*a;
	t_mesh			*b;
	unsigned int	i_a;
	unsigned int	i_b;
	t_vec3d			cam_mesh_first;
	float			norm_dist_first;
	t_vec3d			cam_actual;
	float			norm_actual;
};

struct	s_physics
{
	t_vec3d			last_pos;
	t_dynarray		collides;
	t_dynarray		collides_cam;
	bool			type_move;
	unsigned int	tps;
	float			gravity;
	t_vec3d			gravitax;
	float			crch;
	float			crch_v;
};

void	scan_actuall_collide(t_env *env, t_map *map);
int		physic_engine(t_env *env, t_map *maps);
int		init_physic_engine(t_env *env);
int		init_bounding_box(t_mesh *m);
int		report_collisions(t_env *env);
int		report_cam_collisions(t_env *env, t_map *maps);
int		init_map_physics(t_map *map);

void	translate_mesh(t_map *map, t_mesh *m, t_vec3d t);
void	rotate_mesh(t_mesh *mesh, t_vec3d mesh_center, float angle,
			void (*rotation)(t_vec3d *v, t_vec3d m, float fcos, float fsin));
void	rotate_x(t_vec3d *v, t_vec3d m, float fcos, float fsin);
void	rotate_y(t_vec3d *v, t_vec3d m, float fcos, float fsin);
void	rotate_z(t_vec3d *v, t_vec3d m, float fcos, float fsin);

void	tp_mesh(t_map *map, t_mesh *m, t_vec3d t);
void	tp_mesh_print(t_mesh *m);

void	phy_gravitax_cam(t_env *env, t_mesh *m);

t_vec3d	update_angle(t_env *env, int index);
void	update_speeds_collide(t_env *env);
void	update_speeds_collide_cam(t_env *env, t_mesh *cam, t_map *map);
void	update_positions_gravity(t_env *env);
void	update_positions_cam(t_env *env, t_map *map, t_mesh *cam);

void	color_collides(t_env *env);
void	color_collides_cam(t_env *env);

void	phy_move(t_env *env, bool keys[NB_KEYS], t_map *maps);

void	type_of_plan(t_env *env, t_collide *c, t_map *map);
t_vec3d	set_y_dir(t_env *env, t_map *map);
t_vec3d	phy_move_collide(t_env *env, t_collide *c, t_vec3d dir);
t_vec3d test_dist_wall(t_env *env, t_collide *c, t_vec3d f);

void	stop_position_cam(t_env *env, t_map *maps, t_mesh *cam);
bool	key_move(bool keys[NB_KEYS]);
void	scan_collide(t_collide *c, int i);
void	print_info_phy(t_env *env, t_mesh *cam, t_map *maps);
t_vec3d	phy_handle_space(t_env *e, bool k[NB_KEYS], t_vec3d f);
#endif
