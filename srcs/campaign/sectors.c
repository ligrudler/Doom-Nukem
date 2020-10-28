/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:33:10 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:33:17 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_sectors(t_env *env)
{
	t_camp_env	*cmp_env;

	cmp_env = &env->cmp_env;
	cmp_env->sectors[SECTOR_START_ROOM].map = SCENE_START_ROOM;
	cmp_env->sectors[SECTOR_DUST].map = SCENE_DUST;
}
