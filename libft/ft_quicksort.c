/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:45:05 by gedemais          #+#    #+#             */
/*   Updated: 2018/12/19 18:58:05 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <time.h>

static int	ft_partition(int *tab, int start, int end)
{
	int		i;
	int		j;
	int		pivot;

	i = start - 1;
	j = start;
	pivot = end - 1;
	if (end - start == 2)
	{
		if (tab[start] > tab[end - 1])
			ft_swap(&tab[start], &tab[end - 1]);
		return (0);
	}
	while (i < end - 1 && j < end - 1)
	{
		if (tab[j] <= tab[pivot])
		{
			i++;
			ft_swap(&tab[i], &tab[j]);
		}
		j++;
	}
	ft_swap(&tab[i + 1], &tab[pivot]);
	return (i + 1);
}

int			ft_quicksort(int *tab, int start, int end)
{
	int		j;

	if (start < end - 1)
	{
		j = ft_partition(tab, start, end);
		ft_quicksort(&tab[start], 0, j);
		ft_quicksort(&tab[j + 1], 0, (end - j - 1));
	}
	return (0);
}
