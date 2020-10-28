/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_gravity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:11:12 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/18 20:11:14 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	phy_gravitax_cam(t_env *env, t_mesh *m)
{
	float grav;

	grav = env->phy_env.tps * env->phy_env.gravity * 50;
	env->phy_env.gravitax = (t_vec3d){0, grav, 0, 0};
	m->corp.v = vec_sub(m->corp.v, env->phy_env.gravitax);
	if (env->phy_env.tps < 10)
		env->phy_env.tps += 2.5;
}
