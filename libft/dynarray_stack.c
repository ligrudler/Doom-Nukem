/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:04:36 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/10 18:05:01 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynarray.h"

int			pop_dynarray(t_dynarray *arr, bool front)
{
	int		len;

	len = (arr->nb_cells - 1) * arr->cell_size;
	if (front)
	{
		ft_memcpy(arr->tmp, (void*)(arr->c + arr->cell_size), len);
		ft_memcpy(arr->c, arr->tmp, len);
	}
	if (arr->nb_cells)
		arr->nb_cells--;
	else
		return (-1);
	return (0);
}

int			push_dynarray(t_dynarray *arr, void *src, bool front)
{
	int		len;

	len = arr->nb_cells * arr->cell_size;
	if (check_space(arr))
		return (-1);
	if (front)
	{
		ft_memcpy(arr->tmp, arr->c, len);
		ft_memcpy(arr->c, src, arr->cell_size);
		ft_memcpy((void*)(arr->c + arr->cell_size), arr->tmp, len);
	}
	else
		ft_memcpy((void*)(arr->c + len), src, arr->cell_size);
	return (0);
}

int			replace_dynarray_cell(t_dynarray *arr, void *src, int index)
{
	void	*ptr;

	if (index >= arr->nb_cells)
		return (-1);
	ptr = arr->c + (arr->cell_size * index);
	ft_memcpy(ptr, src, arr->cell_size);
	return (0);
}

int			dynarray_swap_cells(t_dynarray *add, int index1, int index2)
{
	void	*d1;
	void	*d2;

	if (index1 < 0 || index2 < 0 || !add
		|| index1 > add->nb_cells || index2 > add->nb_cells)
		return (-1);
	d1 = dyacc(add, index1);
	d2 = dyacc(add, index2);
	ft_memcpy(add->tmp, d1, add->cell_size);
	ft_memcpy(d1, d2, add->cell_size);
	ft_memcpy(d2, add->tmp, add->cell_size);
	return (0);
}
