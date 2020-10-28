/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_lines_fts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:08:59 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 22:06:34 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		mtl_new(char **toks, t_dynarray *mtls)
{
	t_mtl			m;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (ft_tablen(toks) != 2)
		return (-1);
	while (i < 2)
	{
		j = 0;
		while (toks[i][j])
		{
			if (!ft_isprint(toks[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	m.textured = false;
	if (!(m.name = ft_strdup(toks[1])) || push_dynarray(mtls, &m, false))
		return (-1);
	return (0);
}

int		mtl_color(char **toks, t_dynarray *mtls)
{
	t_mtl			*cm;
	unsigned int	i;
	float			t;

	i = 1;
	if (!(cm = dyacc(mtls, mtls->nb_cells - 1)) || ft_tablen(toks) != 4)
		return (-1);
	ft_memset(&cm->color, 0, sizeof(int));
	while (i < 4)
	{
		if (!check_float(toks[i]))
			return (-1);
		t = ft_atof(toks[i]);
		if (t < 0.0f || t > 1.0f)
			return (-1);
		cm->color[i - 1] = (t * 255);
		i++;
	}
	swap_bytes(&cm->color[0], &cm->color[2]);
	return (0);
}

int		mtl_alpha(char **toks, t_dynarray *mtls)
{
	t_mtl			*cm;

	if (!(cm = dyacc(mtls, mtls->nb_cells - 1)) || ft_tablen(toks) != 2)
		return (-1);
	if ((cm->alpha = ft_atof(toks[1])) < 0.0 || cm->alpha > 1.0f)
		return (-1);
	return (0);
}

int		mtl_map_texture(char **toks, t_dynarray *mtls)
{
	int		i;
	int		j;
	t_mtl	*cm;

	i = -1;
	while (toks[++i])
	{
		j = -1;
		while (toks[i][++j])
			if (!ft_isprint(toks[i][j]))
				return (-1);
	}
	if (!(cm = dyacc(mtls, mtls->nb_cells - 1)))
		return (-1);
	cm->textured = true;
	return (0);
}
