/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle_texture_bis.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:33:06 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 13:13:10 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	starting_swap(t_triangle *t)
{
	if (t->points[1].y < t->points[0].y)
	{
		swap_floats(&t->points[0].y, &t->points[1].y);
		swap_floats(&t->points[0].x, &t->points[1].x);
		t->textured ? swap_floats(&t->txt[0].u, &t->txt[1].u) : 0;
		t->textured ? swap_floats(&t->txt[0].v, &t->txt[1].v) : 0;
		swap_floats(&t->txt[0].w, &t->txt[1].w);
	}
	if (t->points[2].y < t->points[0].y)
	{
		swap_floats(&t->points[2].y, &t->points[0].y);
		swap_floats(&t->points[2].x, &t->points[0].x);
		t->textured ? swap_floats(&t->txt[2].u, &t->txt[0].u) : 0;
		t->textured ? swap_floats(&t->txt[2].v, &t->txt[0].v) : 0;
		swap_floats(&t->txt[2].w, &t->txt[0].w);
	}
	if (t->points[2].y < t->points[1].y)
	{
		swap_floats(&t->points[2].y, &t->points[1].y);
		swap_floats(&t->points[2].x, &t->points[1].x);
		t->textured ? swap_floats(&t->txt[2].u, &t->txt[1].u) : 0;
		t->textured ? swap_floats(&t->txt[2].v, &t->txt[1].v) : 0;
		swap_floats(&t->txt[2].w, &t->txt[1].w);
	}
}

void	compute_steps(t_texturizer *txt, bool t)
{
	if (txt->dy1)
	{
		txt->ax_step = txt->dx1 / txt->dy1;
		if (t)
			txt->u1_step = txt->du1 / txt->dy1;
		if (t)
			txt->v1_step = txt->dv1 / txt->dy1;
		txt->w1_step = txt->dw1 / txt->dy1;
	}
	if (txt->dy2)
	{
		txt->bx_step = txt->dx2 / txt->dy2;
		if (t)
			txt->u2_step = txt->du2 / txt->dy2;
		if (t)
			txt->v2_step = txt->dv2 / txt->dy2;
		txt->w2_step = txt->dw2 / txt->dy2;
	}
}

void	compute_gradients(t_texturizer *txt, t_triangle *t, bool flatbot)
{
	int		a;
	int		b;

	a = flatbot ? 2 : 1;
	b = flatbot ? 1 : 0;
	txt->dx1 = t->points[a].x - t->points[b].x;
	txt->dy1 = t->points[a].y - t->points[b].y;
	txt->du1 = t->textured ? t->txt[a].u - t->txt[b].u : 0;
	txt->dv1 = t->textured ? t->txt[a].v - t->txt[b].v : 0;
	txt->dw1 = t->txt[a].w - t->txt[b].w;
	if (!flatbot)
	{
		txt->dx2 = t->points[2].x - t->points[0].x;
		txt->dy2 = t->points[2].y - t->points[0].y;
		txt->du2 = t->textured ? t->txt[2].u - t->txt[0].u : 0;
		txt->dv2 = t->textured ? t->txt[2].v - t->txt[0].v : 0;
		txt->dw2 = t->txt[2].w - t->txt[0].w;
	}
	compute_steps(txt, t->textured);
}

void	set_line_bounds_top(t_texturizer *txt, t_triangle *t, float current)
{
	txt->ax = t->points[0].x + current * txt->ax_step;
	txt->bx = t->points[0].x + current * txt->bx_step;
	txt->txt_su = t->textured ? t->txt[0].u + current * txt->u1_step : 0;
	txt->txt_sv = t->textured ? t->txt[0].v + current * txt->v1_step : 0;
	txt->txt_sw = t->txt[0].w + current * txt->w1_step;
	txt->txt_eu = t->textured ? t->txt[0].u + current * txt->u2_step : 0;
	txt->txt_ev = t->textured ? t->txt[0].v + current * txt->v2_step : 0;
	txt->txt_ew = t->txt[0].w + current * txt->w2_step;
	if (txt->ax > txt->bx)
	{
		swap_floats(&txt->ax, &txt->bx);
		t->textured ? swap_floats(&txt->txt_su, &txt->txt_eu) : 0;
		t->textured ? swap_floats(&txt->txt_sv, &txt->txt_ev) : 0;
		swap_floats(&txt->txt_sw, &txt->txt_ew);
	}
}

void	set_line_bounds_bot(t_texturizer *txt, t_triangle *t, float currents[2])
{
	txt->ax = t->points[1].x + currents[1] * txt->ax_step;
	txt->bx = t->points[0].x + currents[0] * txt->bx_step;
	txt->txt_su = t->textured ? t->txt[1].u + currents[1] * txt->u1_step : 0;
	txt->txt_sv = t->textured ? t->txt[1].v + currents[1] * txt->v1_step : 0;
	txt->txt_sw = t->txt[1].w + currents[1] * txt->w1_step;
	txt->txt_eu = t->textured ? t->txt[0].u + currents[0] * txt->u2_step : 0;
	txt->txt_ev = t->textured ? t->txt[0].v + currents[0] * txt->v2_step : 0;
	txt->txt_ew = t->txt[0].w + currents[0] * txt->w2_step;
	if (txt->ax > txt->bx)
	{
		swap_floats(&txt->ax, &txt->bx);
		t->textured ? swap_floats(&txt->txt_su, &txt->txt_eu) : 0;
		t->textured ? swap_floats(&txt->txt_sv, &txt->txt_ev) : 0;
		swap_floats(&txt->txt_sw, &txt->txt_ew);
	}
}
