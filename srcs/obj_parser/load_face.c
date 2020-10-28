/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_face.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 03:53:16 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 15:14:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	count_digits(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}

static bool	check_index(char *tok)
{
	int		n_digits;

	n_digits = count_digits(tok);
	if (!ft_inbounds(n_digits, 1, 10))
		return (false);
	if (tok[n_digits] && tok[n_digits] != '/')
		return (false);
	return (true);
}

static bool	check_format(char **toks)
{
	unsigned int	i;
	unsigned int	j;

	i = 1;
	while (toks[i])
	{
		j = 0;
		if (!ft_isdigit(toks[i][j]))
			return (true);
		while (toks[i][j])
		{
			if (!ft_isdigit(toks[i][j]) && toks[i][j] != '/')
				return (true);
			if (ft_isdigit(toks[i][j]) && !check_index(&toks[i][j]))
				return (true);
			j++;
		}
		if (toks[i][j - 1] == '/')
			return (true);
		i++;
	}
	return (false);
}

static void	load_indexes(char **toks, t_face *face, t_mesh *m)
{
	int		offset;

	(void)m;
	face->x = ft_atoi(toks[1]);
	if (face->textured)
	{
		offset = count_digits(toks[1]) + 1;
		face->tx = ft_atoi(&toks[1][offset]);
	}
	face->y = ft_atoi(toks[2]);
	if (face->textured)
	{
		offset = count_digits(toks[2]) + 1;
		face->ty = ft_atoi(&toks[2][offset]);
	}
	face->z = ft_atoi(toks[3]);
	if (face->textured)
	{
		offset = count_digits(toks[3]) + 1;
		face->tz = ft_atoi(&toks[3][offset]);
	}
}

int			load_face(char **toks, t_map *map, t_face *face)
{
	t_mesh	*m;

	if (check_format(toks))
		return (-1);
	if (!(m = dyacc(&map->meshs, map->nmesh - 1)))
		return (-1);
	load_indexes(toks, face, m);
	return (0);
}
