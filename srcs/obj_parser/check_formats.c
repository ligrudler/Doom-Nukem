/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_formats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 20:04:50 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 20:04:52 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	check_float(char *tok)
{
	unsigned int	i;
	unsigned int	dots;
	unsigned int	last_dot;

	i = 0;
	dots = 0;
	while (tok[i])
	{
		if ((tok[i] == '-' || tok[i] == '+') && i > 0)
			return (false);
		if (tok[i] == '.')
		{
			last_dot = i;
			dots++;
		}
		else if (!ft_isdigit(tok[i]) && tok[i] != '-' && tok[i] != '+')
			return (false);
		i++;
	}
	if (dots > 1 || last_dot >= i - 1)
		return (false);
	return (true);
}

bool	check_number(char *tok)
{
	unsigned int		i;

	i = 0;
	while (tok[i])
	{
		if (!ft_isdigit(tok[i]))
			return (false);
		i++;
	}
	if (i > 9 || ft_atoi(tok) > 2147483647)
		return (false);
	return (true);
}
