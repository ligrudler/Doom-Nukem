/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:03:33 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/10 18:03:52 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start_check(t_dynarray *arr, void *src, int index, bool insert)
{
	if (index < 0 || index > arr->nb_cells || check_space(arr))
		return (-1);
	if (index == arr->nb_cells)
	{
		arr->nb_cells--;
		insert ? push_dynarray(arr, src, 0) : pop_dynarray(arr, 0);
		return (1);
	}
	else if (index == 0)
	{
		arr->nb_cells--;
		insert ? push_dynarray(arr, src, 1) : pop_dynarray(arr, 1);
		return (1);
	}
	return (0);
}

int			insert_dynarray(t_dynarray *arr, void *src, int index)
{
	void	*mid;
	int		rest;
	int		ret;

	if ((ret = start_check(arr, src, index, true)))
		return (ret == -1 ? -1 : 0);
	mid = arr->c + (index * arr->cell_size);
	rest = (arr->nb_cells - index) * arr->cell_size;
	ft_memcpy(arr->tmp, mid, rest);
	ft_memcpy(mid, src, arr->cell_size);
	mid += arr->cell_size;
	ft_memcpy(mid, arr->tmp, rest);
	return (0);
}

int			extract_dynarray(t_dynarray *arr, int index)
{
	void	*mid;
	int		rest;
	int		ret;

	if ((ret = start_check(arr, NULL, index, false)))
		return (ret == -1 ? -1 : 0);
	mid = arr->c + (index * arr->cell_size);
	rest = (arr->nb_cells - index - 2) * arr->cell_size;
	ft_memcpy(arr->tmp, mid + arr->cell_size, rest);
	ft_memcpy(mid, arr->tmp, rest);
	arr->nb_cells -= 2;
	return (0);
}
