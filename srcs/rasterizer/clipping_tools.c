/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:47:14 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/12 21:48:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	copy_triangle_stats(t_triangle *tri, t_triangle *t)
{
	tri->textured = t->textured;
	tri->voxel = t->voxel;
	tri->color = t->color;
	tri->normal = t->normal;
	tri->sp = t->sp;
	tri->mesh = t->mesh;
}
