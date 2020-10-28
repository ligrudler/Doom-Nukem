/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_tool3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:11:46 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/18 20:11:47 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vec3d		phy_handle_space(t_env *e, bool k[NB_KEYS], t_vec3d f)
{
	if (k[KEY_SPACE] && e->cam.stats.onwall == 0)
		f.y += 0.3;
	if (f.y > 0 && e->cam.stats.onroof == 1)
	{
		f.y = 0.1;
		e->cam.stats.onfloor = 0;
	}
	return (f);
}

void		scan_collide(t_collide *c, int i)
{
	c->cam_mesh_first = vec_sub(c->b->corp.pos, c->a->corp.pos);
	c->norm_dist_first = vec_norm(c->cam_mesh_first);
	c->i_a = i;
}
