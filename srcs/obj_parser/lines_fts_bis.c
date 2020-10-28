/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_fts_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 20:11:47 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 22:23:45 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		vertex_end(t_map *map, char **toks)
{
	(void)map;
	(void)toks;
	return (0);
}

int		comment(t_map *map, char **toks)
{
	(void)map;
	(void)toks;
	return (0);
}

int		mtllib(t_map *map, char **toks)
{
	unsigned int	i;

	i = 0;
	if (*init_parser())
		return (0);
	if (ft_tablen(toks) != 2 || (map->mtls.byte_size == 0
		&& init_dynarray(&map->mtls, sizeof(t_mtl), 0)))
		return (-1);
	if (parse_mtl(toks[1], &map->mtls))
		return (-1);
	return (0);
}

int		usemtl(t_map *map, char **toks)
{
	t_mtl	*m;
	int		i;

	i = 0;
	if (ft_tablen(toks) != 2)
		return (-1);
	while (i < map->mtls.nb_cells)
	{
		if ((m = dyacc(&map->mtls, i)) && !ft_strcmp(toks[1], m->name))
		{
			map->cmtl = i;
			return (0);
		}
		i++;
	}
	map->cmtl = -1;
	return (-1);
}
