/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:02:41 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/10 18:03:06 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynarray.h"

void		*dyacc(t_dynarray *arr, int index)
{
	if (index > arr->nb_cells || index < 0)
		return (NULL);
	return ((void*)(arr->c + (index * arr->cell_size)));
}

void		free_dynarray(t_dynarray *arr)
{
	free(arr->c);
	free(arr->tmp);
	ft_memset(arr, 0, sizeof(t_dynarray));
}

static int	start_size(int n)
{
	int		a;

	a = 2;
	while (n >= a)
		a *= 2;
	return (a);
}

void		clear_dynarray(t_dynarray *arr)
{
	arr->nb_cells = 0;
}

int			init_dynarray(t_dynarray *arr, int cell_size, int nb_cells)
{
	if (cell_size <= 0 || nb_cells < 0)
		return (-1);
	arr->cell_size = cell_size;
	arr->nb_cells = 0;
	arr->byte_size = start_size(cell_size * nb_cells + 1);
	if (arr->byte_size > 0 && (!(arr->c = malloc(arr->byte_size))
		|| !(arr->tmp = malloc(arr->byte_size))))
		return (-1);
	ft_memset(arr->c, 0, arr->byte_size);
	return (0);
}
