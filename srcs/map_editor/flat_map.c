/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:35:21 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:35:33 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		copy_matrice(t_ed_map *env, int *len)
{
	int	nb[4];

	nb[0] = 0;
	nb[1] = -1;
	while (++nb[1] < env->width)
	{
		nb[2] = -1;
		while (++nb[2] < env->height)
		{
			nb[3] = -1;
			while (++nb[3] < env->depth)
				env->flat[nb[0]++] = env->map[nb[1]][nb[2]][nb[3]];
			if (nb[2] + 1 < env->height)
				env->flat[nb[0]++] = 127;
		}
		if (nb[1] + 1 < env->width)
		{
			env->flat[nb[0]++] = 127;
			env->flat[nb[0]++] = 127;
		}
	}
	env->flat[nb[0]] = '\0';
	*len = nb[0];
}

int				flat_map(t_ed_map *env, int *len)
{
	int		size;

	if (env->map == NULL
		|| env->width + env->height + env->depth == 0)
		return (0);
	size = (env->width + 1) * (env->height + 2) * env->depth;
	if (!(env->flat = (unsigned char*)ft_memalloc(size + 1)))
		return (0);
	copy_matrice(env, len);
	return (1);
}
