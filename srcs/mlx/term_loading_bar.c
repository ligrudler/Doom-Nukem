/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_loading_bar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 03:46:37 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/08 20:23:05 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	fill_blank(unsigned int j, unsigned int max)
{
	while (j < max - 1)
	{
		ft_putchar(' ');
		j++;
	}
}

void		loading_bar(unsigned int i, unsigned int max, bool last)
{
	unsigned int	j;

	j = 0;
	if (last)
	{
		ft_putchar('\n');
		return ;
	}
	ft_putchar('[');
	ft_putstr(L_GREEN);
	while (j < i)
	{
		ft_putchar('-');
		j++;
	}
	ft_putstr(L_RED);
	ft_putchar('>');
	ft_putstr(STOP);
	fill_blank(j, max);
	ft_putstr(L_GREEN);
	ft_putchar(']');
	ft_putstr(STOP);
}
