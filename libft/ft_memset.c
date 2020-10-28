/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:22:48 by gedemais          #+#    #+#             */
/*   Updated: 2020/05/27 18:43:03 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	tmp_c;
	unsigned long	*longword_ptr;
	unsigned long	magicbit;

	i = 0;
	tmp_c = (unsigned char)c;
	magicbit = (~0UL / 255) * (unsigned char)c;
	while (i < len % 8)
		((unsigned char*)b)[i++] = tmp_c;
	longword_ptr = (unsigned long*)(b + i);
	while (i < len)
	{
		*longword_ptr++ = magicbit;
		i += 8;
	}
	return (b);
}
