/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 01:58:00 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:34:29 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_buzzers(t_env *e)
{
	t_camp_env	*env;

	env = &e->cmp_env;
	env->buzzers[0].start = dyacc(&e->maps[SCENE_DUST].meshs, 1);
	env->buzzers[1].start = dyacc(&e->maps[SCENE_DUST].meshs, 7);
	env->buzzers[2].start = dyacc(&e->maps[SCENE_DUST].meshs, 8);
	env->buzzers[3].start = dyacc(&e->maps[SCENE_DUST].meshs, 3);
	env->buzzers[4].start = dyacc(&e->maps[SCENE_DUST].meshs, 4);
	env->buzzers[5].start = dyacc(&e->maps[SCENE_DUST].meshs, 11);
	env->buzzers[0].buzzer = dyacc(&e->maps[SCENE_START_ROOM].meshs, 18);
	env->buzzers[1].buzzer = dyacc(&e->maps[SCENE_START_ROOM].meshs, 19);
	env->buzzers[2].buzzer = dyacc(&e->maps[SCENE_START_ROOM].meshs, 20);
	env->buzzers[3].buzzer = dyacc(&e->maps[SCENE_START_ROOM].meshs, 14);
	env->buzzers[4].buzzer = dyacc(&e->maps[SCENE_START_ROOM].meshs, 21);
	env->buzzers[5].buzzer = dyacc(&e->maps[SCENE_START_ROOM].meshs, 22);
	env->buzzers[0].pos = (t_vec3d){-1, 1, -14, 0};
	env->buzzers[1].pos = (t_vec3d){2, 0.3, -4.5, 0};
	env->buzzers[2].pos = (t_vec3d){-0.4, 0.5, 6.15, 0};
	env->buzzers[3].pos = (t_vec3d){-11, -0.4, -14, 0};
	env->buzzers[4].pos = (t_vec3d){-20.3, 1, -0.78, 0};
	env->buzzers[5].pos = (t_vec3d){15.92, 1.24, -14.75, 0};
}

static void	init_buttons_cmp(t_env *env)
{
	t_camp_env	*cmp_env;
	t_button	*b;
	t_sprite	*sps[3];

	cmp_env = &env->cmp_env;
	b = &cmp_env->buttons[CMP_BUTTON_MAIN_MENU];
	sps[0] = &env->sprites[SP_CP_BUTTON_1C];
	sps[1] = &env->sprites[SP_CP_BUTTON_1H];
	sps[2] = &env->sprites[SP_CP_BUTTON_1O];
	init_button(b, (t_point){70, 600}, sps);
	b = &cmp_env->buttons[CMP_BUTTON_NEW_GAME];
	sps[0] = &env->sprites[SP_CP_BUTTON_2C];
	sps[1] = &env->sprites[SP_CP_BUTTON_2H];
	sps[2] = &env->sprites[SP_CP_BUTTON_2O];
	init_button(b, (t_point){330, 600}, sps);
}

int			setup_cmp(t_env *env)
{
	env->cmp_env.env = env;
	init_buttons_cmp(env);
	init_sectors(env);
	init_buzzers(env);
	env->cmp_env.door = (t_vec3d){-15, 2.8, -0.13, 0};
	env->cmp_env.hint_t = 2;
	return (0);
}
