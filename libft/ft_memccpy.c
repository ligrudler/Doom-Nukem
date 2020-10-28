/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:21:51 by gedemais          #+#    #+#             */
/*   Updated: 2018/11/08 09:01:09 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*d;
	char			*s;
	unsigned int	i;

	s = (char*)src;
	d = (char*)dst;
	i = 0;
	while (n--)
	{
		d[i] = s[i];
		if (s[i++] == (char)c)
			return ((char*)dst + i);
	}
	return (NULL);
}
