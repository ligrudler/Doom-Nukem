/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_to_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:34:40 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/17 14:34:57 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_mesh	*copy_to_scene(t_map *dest, t_map *src, t_vec3d pos)
{
	t_mesh		new;
	t_mesh		*m;
	t_mesh		*ret;
	int			i;

	i = 0;
	ret = dest->meshs.c + (dest->meshs.cell_size * dest->meshs.nb_cells);
	while (i < src->meshs.nb_cells)
	{
		ft_memset(&new, 0, sizeof(t_mesh));
		m = dyacc(&src->meshs, i);
		new.type = 1;
		new.index = dest->nmesh;
		if (init_dynarray(&new.tris, sizeof(t_triangle), 12)
			|| copy_triangles(dest, src, m, &new)
			|| push_dynarray(&dest->meshs, &new, false))
			return (NULL);
		assign_meshs(dyacc(&dest->meshs, dest->nmesh));
		translate_mesh(dest, dyacc(&dest->meshs, dest->nmesh), pos);
		dest->nmesh++;
		i++;
	}
	return (ret);
}
