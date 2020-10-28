/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 20:13:24 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 20:13:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			load_maps(t_env *env)
{
	char			states[PS_MAX][PS_MAX];
	unsigned int	i;

	i = 0;
	ft_putendl("Loading maps...");
	init_states(states);
	while (i < SCENE_MAX)
	{
		loading_bar(i, SCENE_MAX, false);
		if (parse_map(&env->maps[i], maps_paths(i), states) != 0)
			return (-1);
		*current_map() = &env->maps[i];
		if (load_map_config(env, &env->maps[i], maps_paths(i)))
			return (-1);
		ft_putchar(i == SCENE_MAX - 1 ? '\0' : '\r');
		env->maps[i].index = i;
		i++;
	}
	loading_bar(i, SCENE_MAX, true);
	return (0);
}
