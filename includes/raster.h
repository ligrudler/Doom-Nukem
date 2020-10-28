/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/21 18:50:52 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RASTER_H
# define RASTER_H

# define MIN_TO_RASTER 16384
# define MIN_TO_CLIP 256
# define NB_OBJ_TYPES 4
# define OBJS_MAX 10000

struct			s_point
{
	int			x;
	int			y;
};

struct			s_filler
{
	float		m0;
	float		m1;
	float		x0;
	float		x1;
	float		xstart;
	float		xend;
	float		ystart;
	float		yend;
	float		xstep;
	float		ystep;
	float		tx;
	float		ty;
	float		w;
};

struct			s_texturizer
{
	t_sprite	*texture;
	float		txt_u;
	float		txt_v;
	float		txt_w;
	float		t_step;
	float		ax;
	float		bx;
	float		txt_su;
	float		txt_sv;
	float		txt_sw;
	float		txt_eu;
	float		txt_ev;
	float		txt_ew;
	float		dx1;
	float		dx2;
	float		dy1;
	float		dy2;
	float		du1;
	float		dv1;
	float		du2;
	float		dv2;
	float		dw1;
	float		dw2;
	float		ax_step;
	float		bx_step;
	float		u1_step;
	float		v1_step;
	float		w1_step;
	float		u2_step;
	float		v2_step;
	float		w2_step;
};

struct			s_clipper
{
	t_vec3d		in[3];
	t_vec3d		out[3];
	t_vec2d		txt_in[3];
	t_vec2d		txt_out[3];
	int			txt_inside;
	int			txt_outside;
	int			inside;
	int			outside;
	float		d[3];
};

struct			s_rasthread
{
	void		*env;
	t_dynarray	*tris;
	pthread_t	thread;
	int			start;
	int			end;
	bool		mono;
	int			index;
	int			id;
};

struct			s_cam_stats
{
	t_vec3d		pos;
	t_vec3d		dir;
	t_vec3d		acc;
	int			speed;
	int			onfloor;
	int			onroof;
	int			onwall;
	int			crouch;
	float		yaw;
	float		pitch;
	float		aspect_ratio;
	float		fnear;
	float		ffar;
	float		fdelta;
	float		fovd;
	float		fovr;
};

struct			s_cam
{
	t_cam_stats	stats;
	t_dynarray	to_clip;
	t_dynarray	to_raster;
	t_dynarray	clip_arrs[4];
	t_vec3d		light;
	float		*z_buffer;
	float		w_m[4][4];
	float		c_m[4][4];
	float		cr_m[4][4];
	float		crx_m[4][4];
	float		cry_m[4][4];
	float		v_m[4][4];
	float		p_m[4][4];
	float		rx_m[4][4];
	float		ry_m[4][4];
	float		rz_m[4][4];
};

int				triangle_pipeline(t_env *env, t_triangle *t,
					t_dynarray *tris, t_mesh *m);
int				raster_triangles(t_env *env, t_dynarray *arr);
void			monothread_raster(void *env);
void			*rasthreader(void *param);
int				rasterizer(t_env *env, t_map *map, bool respawn);
int				raster_weapon(t_env *env, t_map *map);
void			map_spawn(t_cam *cam, t_map *map, bool respawn);
void			camera_aim(t_env *env);

/*
** Clipping
*/
int				init_camera(t_env *env, t_cam *cam);
int				init_cameras_mesh(t_map *map, t_mesh *cam);
int				allocate_clipping_arrays(t_dynarray arrays[4]);
void			classify_triangle(t_clipper *clip, t_triangle in);
bool			is_triangle_in_screen(t_triangle t);
int				refactor_triangle(t_clipper *clip,
					t_triangle out[2], t_vec3d planes[2], t_triangle t);
int				clip_mesh_triangles(t_dynarray *tris,
					t_dynarray *to_raster, t_dynarray arrs[4]);
int				clip_triangle(t_vec3d plane_p,
					t_vec3d plane_n, t_triangle in, t_triangle out[2]);
void			copy_triangle_stats(t_triangle *tri, t_triangle *t);

/*
** Matrices
*/
void			init_matrices(t_cam *cam);
void			translation_matrix(float m[4][4], t_vec3d v);
void			update_xrotation_matrix(float m[4][4], float theta);
void			update_yrotation_matrix(float m[4][4], float theta);
void			update_zrotation_matrix(float m[4][4], float theta);
t_vec3d			multiply_matrix(float m[4][4], t_vec3d o);
t_vec3d			matrix_mult_vec(float m[4][4], t_vec3d i);
void			matrix_mult_matrix(float m1[4][4],
					float m2[4][4], float ret[4][4]);
void			matrix_pointat(float m[4][4],
					t_vec3d pos, t_vec3d target, t_vec3d up);
void			inverse_matrix(float m[4][4], float ret[4][4]);

/*
** Texturing
*/
void			draw_triangle_line(t_env *env,
					t_texturizer *txt, t_triangle *t, int i);
void			starting_swap(t_triangle *t);
void			compute_steps(t_texturizer *txt, bool t);
void			compute_gradients(t_texturizer *txt,
					t_triangle *t, bool flatbot);
void			set_line_bounds_top(t_texturizer *txt,
					t_triangle *t, float current);
void			set_line_bounds_bot(t_texturizer *txt,
					t_triangle *t, float currents[2]);
void			fill_triangle_texture(t_env *env, t_triangle *t);

/*
** Tools
*/
void			draw_triangle(void *mlx, t_triangle t);
void			compute_rotation_matrices(t_env *env);
void			compute_view_matrice(t_env *env);
void			swap_floats(float *a, float *b);
void			clear_screen_buffers(t_env *env);

void			print_first_mesh(t_env *env);
#endif
