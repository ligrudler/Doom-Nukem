/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:40:39 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 14:40:59 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		back_n_forth(t_weapon *w, float progress, bool reset)
{
	t_vec3d		new_pos;

	ft_bzero(&new_pos, sizeof(t_vec3d));
	if (progress < 0.5f)
		w->w_map->spawn.z += w->recoil;
	else
		w->w_map->spawn.z -= w->recoil;
	if (reset || w->w_map->spawn.y < w->start.y)
		w->w_map->spawn = w->start;
}

void			shoot_animation(t_env *env, t_weapon *w)
{
	float	progress;

	w->shooting -= env->data.spent;
	progress = 1 - (w->shooting / (60.0f / w->cadency));
	progress = (progress > 1.0f) ? 1.0f : progress;
	progress = (progress < 0.0f) ? 0.0f : progress;
	back_n_forth(w, progress, progress > 0.75f);
}
