/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:16:06 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/16 19:04:06 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				dup_names(t_env *env)
{
	const char		*names[W_MAX] = {"FAMAS", "AK-47", "Sawed-Off", "Glock-18",
									"AUG", "UMP45", "mag-7", "Galil", "Negev",
									"TEC-9"};
	unsigned int	i;

	i = 0;
	while (i < W_MAX)
	{
		if (!(env->weapons[i].name = ft_strdup((char*)names[i])))
			return (-1);
		env->weapons[i].start = env->weapons[i].w_map->spawn;
		env->weapons[i].index = (int)i;
		i++;
	}
	return (0);
}

static void		assign_wmeshs_bis(t_env *env)
{
	env->weapons[W_UMP45].mesh = env->maps[SCENE_UMP45].meshs.c;
	env->weapons[W_UMP45].breech = dyacc(&env->maps[SCENE_UMP45].meshs, 2);
	env->weapons[W_UMP45].w_map = &env->maps[SCENE_UMP45];
	env->weapons[W_MAG7].mesh = env->maps[SCENE_MAG7].meshs.c;
	env->weapons[W_MAG7].breech = dyacc(&env->maps[SCENE_MAG7].meshs, 1);
	env->weapons[W_MAG7].w_map = &env->maps[SCENE_MAG7];
	env->weapons[W_GALIL].mesh = env->maps[SCENE_GALIL].meshs.c;
	env->weapons[W_GALIL].breech = dyacc(&env->maps[SCENE_GALIL].meshs, 2);
	env->weapons[W_GALIL].w_map = &env->maps[SCENE_GALIL];
	env->weapons[W_NEGEV].mesh = env->maps[SCENE_NEGEV].meshs.c;
	env->weapons[W_NEGEV].breech = dyacc(&env->maps[SCENE_NEGEV].meshs, 2);
	env->weapons[W_NEGEV].w_map = &env->maps[SCENE_NEGEV];
	env->weapons[W_TEC9].mesh = env->maps[SCENE_TEC9].meshs.c;
	env->weapons[W_TEC9].breech = dyacc(&env->maps[SCENE_TEC9].meshs, 2);
	env->weapons[W_TEC9].w_map = &env->maps[SCENE_TEC9];
}

static void		assign_wmeshs(t_env *env)
{
	t_map	*maps;

	maps = &env->maps[0];
	env->weapons[W_FAMAS].mesh = maps[SCENE_FAMAS].meshs.c;
	env->weapons[W_FAMAS].breech = dyacc(&maps[SCENE_FAMAS].meshs, 2);
	env->weapons[W_FAMAS].w_map = &maps[SCENE_FAMAS];
	env->weapons[W_AK47].mesh = maps[SCENE_AK47].meshs.c;
	env->weapons[W_AK47].breech = dyacc(&maps[SCENE_AK47].meshs, 1);
	env->weapons[W_AK47].w_map = &maps[SCENE_AK47];
	env->weapons[W_SAWED_OFF].mesh = maps[SCENE_SAWED_OFF].meshs.c;
	env->weapons[W_SAWED_OFF].breech = dyacc(&maps[SCENE_SAWED_OFF].meshs, 1);
	env->weapons[W_SAWED_OFF].w_map = &maps[SCENE_SAWED_OFF];
	env->weapons[W_GLOCK_18].mesh = maps[SCENE_GLOCK_18].meshs.c;
	env->weapons[W_GLOCK_18].breech = dyacc(&maps[SCENE_GLOCK_18].meshs, 2);
	env->weapons[W_GLOCK_18].w_map = &maps[SCENE_GLOCK_18];
	env->weapons[W_AUG].mesh = maps[SCENE_AUG].meshs.c;
	env->weapons[W_AUG].breech = dyacc(&maps[SCENE_AUG].meshs, 2);
	env->weapons[W_AUG].w_map = &maps[SCENE_AUG];
	assign_wmeshs_bis(env);
}

static void		assign_weapons_samples(t_env *env)
{
	env->weapons[W_FAMAS].shoot = SA_FAMAS_FIRE;
	env->weapons[W_AK47].shoot = SA_AK47_FIRE;
	env->weapons[W_SAWED_OFF].shoot = SA_SAWED_OFF_FIRE;
	env->weapons[W_GLOCK_18].shoot = SA_GLOCK_FIRE;
	env->weapons[W_AUG].shoot = SA_AUG_FIRE;
	env->weapons[W_UMP45].shoot = SA_UMP45_FIRE;
	env->weapons[W_MAG7].shoot = SA_MAG7_FIRE;
	env->weapons[W_GALIL].shoot = SA_GALIL_FIRE;
	env->weapons[W_NEGEV].shoot = SA_NEGEV_FIRE;
	env->weapons[W_TEC9].shoot = SA_TEC9_FIRE;
	env->weapons[W_FAMAS].reload = SA_FAMAS_RELOAD;
	env->weapons[W_AK47].reload = SA_AK47_RELOAD;
	env->weapons[W_SAWED_OFF].reload = SA_SAWED_OFF_FILL;
	env->weapons[W_GLOCK_18].reload = SA_GLOCK_RELOAD;
	env->weapons[W_AUG].reload = SA_AUG_RELOAD;
	env->weapons[W_UMP45].reload = SA_UMP45_RELOAD;
	env->weapons[W_MAG7].reload = SA_MAG7_RELOAD;
	env->weapons[W_GALIL].reload = SA_GALIL_RELOAD;
	env->weapons[W_NEGEV].reload = SA_NEGEV_RELOAD;
	env->weapons[W_TEC9].reload = SA_TEC9_RELOAD;
}

int				init_weapons(t_env *env)
{
	assign_wmeshs(env);
	assign_weapons_stats(env);
	assign_weapons_samples(env);
	if (dup_names(env))
		return (-1);
	return (0);
}
