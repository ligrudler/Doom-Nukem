/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 04:33:11 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 13:26:55 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	clear_screen_buffers(t_env *env)
{
	static int		size = HGT * WDT;
	int				i;

	i = 0;
	ft_memset(env->mlx.img_data, 0, env->data.data_size);
	while (i < size - 4)
	{
		env->cam.z_buffer[i] = -INFINITY;
		env->cam.z_buffer[i + 1] = -INFINITY;
		env->cam.z_buffer[i + 2] = -INFINITY;
		env->cam.z_buffer[i + 3] = -INFINITY;
		i += 4;
	}
	env->mid.mesh = NULL;
}

void	compute_rotation_matrices(t_env *env)
{
	update_xrotation_matrix(env->cam.rx_m, 0);
	update_yrotation_matrix(env->cam.ry_m, 0);
	update_zrotation_matrix(env->cam.rz_m, 0);
	matrix_mult_matrix(env->cam.rz_m, env->cam.rx_m, env->cam.w_m);
}

void	compute_view_matrice(t_env *env)
{
	t_vec3d	up;
	t_vec3d	target;
	float	yaw_rad;
	float	pitch_rad;

	env->cam.stats.dir = (t_vec3d){0, 0, 1, 0};
	up = (t_vec3d){0, -1, 0, 0};
	target = (t_vec3d){0, 0, 1, 0};
	yaw_rad = ft_to_radians(env->cam.stats.yaw);
	pitch_rad = ft_to_radians(env->cam.stats.pitch);
	update_yrotation_matrix(env->cam.cry_m, yaw_rad);
	update_xrotation_matrix(env->cam.crx_m, pitch_rad);
	matrix_mult_matrix(env->cam.crx_m, env->cam.cry_m, env->cam.cr_m);
	env->cam.stats.dir = matrix_mult_vec(env->cam.cr_m, target);
	up = matrix_mult_vec(env->cam.cr_m, (t_vec3d){0, -1, 0, 0});
	target = vec_add(env->cam.stats.pos, env->cam.stats.dir);
	matrix_pointat(env->cam.c_m, env->cam.stats.pos, target, up);
	inverse_matrix(env->cam.c_m, env->cam.v_m);
}

void	swap_floats(float *a, float *b)
{
	float	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	draw_triangle(void *mlx, t_triangle t)
{
	t_point		a;
	t_point		b;
	t_point		c;

	a = (t_point){t.points[0].x, t.points[0].y};
	b = (t_point){t.points[1].x, t.points[1].y};
	c = (t_point){t.points[2].x, t.points[2].y};
	draw_line((t_mlx*)mlx, a, b, 0x00ff00);
	draw_line((t_mlx*)mlx, a, c, 0x00ff00);
	draw_line((t_mlx*)mlx, b, c, 0x00ff00);
}
