/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dependencies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 20:05:06 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 20:05:16 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	seek_cycle(t_dynarray *meshs, t_mesh *m, t_mesh *master)
{
	int		dep;
	int		i;

	i = 0;
	while (i < m->deps.nb_cells)
	{
		dep = *(int*)dyacc(&m->deps, i);
		if (master->index == dep
			|| seek_cycle(meshs, dyacc(meshs, dep), master))
			return (-1);
		i++;
	}
	return (0);
}

int			check_deps_cycle(t_dynarray *meshs)
{
	t_mesh		*m;
	int			i;

	i = 0;
	while (i < meshs->nb_cells)
	{
		if (!(m = dyacc(meshs, i)) || seek_cycle(meshs, m, m))
		{
			ft_putstr_fd("Dependencie cycle detected on mesh ", 2);
			ft_putendl_fd(m->name, 2);
			return (-1);
		}
		i++;
	}
	return (0);
}
