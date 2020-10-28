/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:26:56 by gedemais          #+#    #+#             */
/*   Updated: 2019/01/12 18:12:16 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	long long int	size;

	size = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[size] != '\0')
	{
		if (s[size + 1] == '\0' || s[size + 2] == '\0')
			return ((s[size + 1] == '\0') ? size + 1 : size + 2);
		else if (s[size + 3] == '\0' || s[size + 4] == '\0')
			return ((s[size + 3] == '\0') ? size + 3 : size + 4);
		else if (s[size + 5] == '\0' || s[size + 6] == '\0')
			return ((s[size + 5] == '\0') ? size + 5 : size + 6);
		else if (s[size + 7] == '\0' || s[size + 8] == '\0')
			return ((s[size + 7] == '\0') ? size + 7 : size + 8);
		else if (s[size + 9] == '\0' || s[size + 10] == '\0')
			return ((s[size + 9] == '\0') ? size + 9 : size + 10);
		else if (s[size + 11] == '\0' || s[size + 12] == '\0')
			return ((s[size + 11] == '\0') ? size + 11 : size + 12);
		else if (s[size + 13] == '\0' || s[size + 14] == '\0')
			return ((s[size + 13] == '\0') ? size + 13 : size + 14);
		size += 15;
	}
	return (size);
}
