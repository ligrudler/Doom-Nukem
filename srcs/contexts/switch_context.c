/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_context.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:24:57 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/08 20:18:42 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	open_gates(bool gates[C_MAX][C_MAX])
{
	gates[C_TITLE_SCREEN][C_CAMPAIGN] = true;
	gates[C_TITLE_SCREEN][C_CUSTOM] = true;
	gates[C_TITLE_SCREEN][C_MAP_EDITOR] = true;
	gates[C_CAMPAIGN][C_TITLE_SCREEN] = true;
	gates[C_CAMPAIGN][C_CUSTOM] = false;
	gates[C_CAMPAIGN][C_MAP_EDITOR] = false;
	gates[C_CUSTOM][C_TITLE_SCREEN] = true;
	gates[C_CUSTOM][C_CAMPAIGN] = false;
	gates[C_CUSTOM][C_MAP_EDITOR] = false;
	gates[C_MAP_EDITOR][C_TITLE_SCREEN] = true;
	gates[C_MAP_EDITOR][C_CAMPAIGN] = false;
	gates[C_MAP_EDITOR][C_CUSTOM] = false;
}

void	init_routines(void (*routines[C_MAX][C_MAX])(t_env*))
{
	routines[C_TITLE_SCREEN][C_CAMPAIGN] = ts_to_campaign;
	routines[C_TITLE_SCREEN][C_CUSTOM] = ts_to_custom;
	routines[C_TITLE_SCREEN][C_MAP_EDITOR] = ts_to_map_editor;
	routines[C_CAMPAIGN][C_TITLE_SCREEN] = campaign_to_ts;
	routines[C_CUSTOM][C_TITLE_SCREEN] = custom_to_ts;
	routines[C_MAP_EDITOR][C_TITLE_SCREEN] = map_editor_to_ts;
}

int		switch_context(t_env *env, unsigned int i)
{
	static bool		first = true;
	static bool		gates[C_MAX][C_MAX];
	static void		(*routines[C_MAX][C_MAX])(t_env*);

	if (first)
	{
		open_gates(gates);
		init_routines(routines);
	}
	if (i >= C_MAX || !gates[env->context][i])
	{
		ft_putstr_fd(ICS_ERR, 2);
		return (-1);
	}
	if (routines[env->context][i])
		routines[env->context][i](env);
	env->context = i;
	first = false;
	return (0);
}
