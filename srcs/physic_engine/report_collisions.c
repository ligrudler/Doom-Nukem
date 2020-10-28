/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report_collisions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 20:12:01 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/18 20:12:03 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	aabb_collision(t_vec3d abo, t_vec3d bbo, t_vec3d abd, t_vec3d bbd)
{
	if ((bbo.x >= abo.x + abd.x)
		|| (bbo.x + bbd.x <= abo.x)
		|| (bbo.y >= abo.y + abd.y)
		|| (bbo.y + bbd.y <= abo.y)
		|| (bbo.z >= abo.z + abd.z)
		|| (bbo.z + bbd.z <= abo.z))
		return (false);
	return (true);
}

static bool	check_coll(t_dynarray *meshs, int i, int j, t_collide *c)
{
	t_mesh	*a;
	t_mesh	*b;

	a = dyacc(meshs, i);
	b = dyacc(meshs, j);
	c->a = a;
	c->b = b;
	return (aabb_collision(a->corp.o, b->corp.o, a->corp.dims, b->corp.dims));
}

static bool	check_coll_cam(t_dynarray *meshs, int i, t_mesh *cm, t_collide *c)
{
	t_mesh	*a;

	a = dyacc(meshs, i);
	if (a->type == 0)
		return (false);
	c->a = a;
	c->b = cm;
	return (aabb_collision(a->corp.o, cm->corp.o, a->corp.dims, cm->corp.dims));
}

int			report_cam_collisions(t_env *env, t_map *maps)
{
	int			i;
	t_collide	c;
	t_mesh		*cam;

	cam = &maps->cam;
	if (!env->phy_env.collides_cam.byte_size
		&& init_dynarray(&env->phy_env.collides_cam,
		sizeof(t_collide), maps->nmesh))
		return (-1);
	i = 0;
	while (i < maps->nmesh)
	{
		if (check_coll_cam(&maps->meshs, i, cam, &c))
		{
			scan_collide(&c, i);
			if (push_dynarray(&env->phy_env.collides_cam, &c, false))
				return (-1);
		}
		i++;
	}
	return (0);
}

int			report_collisions(t_env *env)
{
	int			i;
	int			j;
	t_collide	c;

	i = 0;
	if (env->phy_env.collides.byte_size == 0
		&& init_dynarray(&env->phy_env.collides,
		sizeof(t_collide), env->maps[env->scene].nmesh))
		return (-1);
	while (i < env->maps[env->scene].nmesh)
	{
		j = -1;
		while (++j < env->maps[env->scene].nmesh)
			if (i != j && !env->maps[env->scene].stats[i]
				&& check_coll(&env->maps[env->scene].meshs, i, j, &c))
			{
				c.i_a = i;
				c.i_b = j;
				if (push_dynarray(&env->phy_env.collides, &c, false))
					return (-1);
			}
		i++;
	}
	return (0);
}
