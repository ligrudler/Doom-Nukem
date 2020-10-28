/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:51:39 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 17:25:23 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		init_me_routines(
							int (*routines[MAPED_SC_MAX][MAPED_SC_MAX])(t_env*))
{
	routines[MAPED_SC_MENU][MAPED_SC_NEW_MAP] = me_menu_to_new_map;
	routines[MAPED_SC_MENU][MAPED_SC_CREATIVE] = me_menu_to_creative;
	routines[MAPED_SC_NEW_MAP][MAPED_SC_CREATIVE] = me_new_map_to_creative;
	routines[MAPED_SC_NEW_MAP][MAPED_SC_MENU] = me_new_map_to_menu;
	routines[MAPED_SC_CREATIVE][MAPED_SC_NEW_MAP] = NULL;
	routines[MAPED_SC_CREATIVE][MAPED_SC_MENU] = me_creative_to_menu;
}

int				switch_mecontext(t_env *env, unsigned int i)
{
	t_edit_env		*edit_env;
	static bool		first = true;
	static int		(*routines[MAPED_SC_MAX][MAPED_SC_MAX])(t_env*);

	edit_env = &env->edit_env;
	if (first)
		init_me_routines(routines);
	if (i >= MAPED_SC_MAX)
	{
		ft_putendl_fd(ICS_ERR, 2);
		return (-1);
	}
	if (routines[edit_env->sub_context][i])
		routines[edit_env->sub_context][i](env);
	edit_env->sub_context = i;
	first = false;
	return (0);
}

int				render_maped(void *param)
{
	static int	(*sub_contexts[MAPED_SC_MAX])(t_env *env) = {maped_menu,
												maped_new_map, maped_creative};
	t_env		*env;

	env = ((t_env*)param);
	return (sub_contexts[env->edit_env.sub_context](env));
}
