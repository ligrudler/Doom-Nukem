/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_matrice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:20:48 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:24:38 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		handle_backline(t_ed_map *env, int *nb, int len)
{
	++nb[2];
	if (env->width == 0)
		env->width = nb[0] - nb[1];
	else if (env->width != nb[0] - nb[1])
		return (0);
	if (env->flat[nb[0] + 1] == 127)
	{
		if (env->height == 0)
			env->height = nb[2];
		else if (env->height != nb[2])
			return (0);
		nb[2] = 0;
		++nb[3];
		++nb[0];
	}
	return (nb[0] + 1 != len);
}

static int		handle_endline(t_ed_map *env, int *nb)
{
	++nb[2];
	++nb[3];
	if (env->width != nb[0] - nb[1])
		return (0);
	if (env->height == 0)
		env->height = nb[2];
	if (env->depth == 0)
		env->depth = nb[3];
	return (env->height == nb[2]);
}

static int		get_matrice_size(t_ed_map *env, int len)
{
	int nb[4];

	nb[2] = 0;
	nb[3] = 0;
	nb[0] = -1;
	while (++nb[0] < len)
	{
		nb[1] = nb[0];
		while (nb[0] < len && env->flat[nb[0]] != 127)
			++nb[0];
		if (env->flat[nb[0]] == 127)
		{
			if (handle_backline(env, nb, len) == 0)
				return (0);
		}
		else if (nb[0] == len)
		{
			if (handle_endline(env, nb) == 0)
				return (0);
		}
	}
	ft_swap(&env->width, &env->depth);
	return (env->width && env->height && env->depth);
}

static void		stock_matrice(t_ed_map *env)
{
	int w;
	int d;
	int h;
	int i;

	i = 0;
	w = -1;
	while (++w < env->width)
	{
		h = -1;
		while (++h < env->height)
		{
			d = -1;
			while (++d < env->depth)
			{
				while (env->flat[i] == 127)
					++i;
				env->map[w][h][d] = env->flat[i];
				++i;
			}
		}
	}
}

int				flat_to_matrice(t_ed_map *env, int offset, int len)
{
	env->flat += offset;
	env->width = 0;
	env->height = 0;
	env->depth = 0;
	len -= offset;
	if (env->flat == NULL
		|| get_matrice_size(env, len) == 0
		|| init_matrice(env) == 0)
	{
		env->flat -= offset;
		return (0);
	}
	stock_matrice(env);
	env->flat -= offset;
	return (1);
}
