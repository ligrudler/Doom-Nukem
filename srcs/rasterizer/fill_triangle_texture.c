/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:50:11 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 13:41:48 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	flattop(t_env *env, t_texturizer *txt, t_triangle *t)
{
	int		i;
	int		end;

	i = ceil(t->points[0].y);
	end = ceil(t->points[1].y);
	while (i < end)
	{
		set_line_bounds_top(txt, t, i - t->points[0].y);
		txt->txt_u = txt->txt_su;
		txt->txt_v = txt->txt_sv;
		txt->txt_w = txt->txt_sw;
		draw_triangle_line(env, txt, t, i);
		i++;
	}
}

static void	flatbot(t_env *env, t_texturizer *txt, t_triangle *t)
{
	int		i;
	int		end;

	i = ceil(t->points[1].y);
	end = ceil(t->points[2].y);
	while (i < end)
	{
		set_line_bounds_bot(txt, t, (float[2]){i - t->points[0].y,
														i - t->points[1].y});
		txt->txt_u = txt->txt_su;
		txt->txt_v = txt->txt_sv;
		txt->txt_w = txt->txt_sw;
		draw_triangle_line(env, txt, t, i);
		i++;
	}
}

static void	load_triangle_data(t_env *env, t_triangle *t, t_texturizer *txt)
{
	if (t->voxel)
		txt->texture = &env->edit_env.btxts[t->sp];
	else if (t->textured && env->context != C_CUSTOM)
		txt->texture = dyacc(&env->maps[env->scene].txts, t->sp);
	else if (t->textured && env->context == C_CUSTOM)
		txt->texture = dyacc(&env->edit_env.map.txts, t->sp);
}

void		fill_triangle_texture(t_env *env, t_triangle *t)
{
	t_texturizer	txt;

	ft_bzero(&txt, sizeof(t_texturizer));
	starting_swap(t);
	load_triangle_data(env, t, &txt);
	compute_gradients(&txt, t, false);
	if (txt.dy1)
		flattop(env, &txt, t);
	compute_gradients(&txt, t, true);
	if (txt.dy1)
		flatbot(env, &txt, t);
}
