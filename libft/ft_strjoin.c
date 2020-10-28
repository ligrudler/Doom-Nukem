/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:26:35 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/13 17:50:50 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	size;

	if (!s1)
		return ((char*)s2);
	if (!s2)
		return ((char*)s1);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(dest = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memset(dest, 0, size);
	ft_strcat(dest, s1);
	ft_strcat(dest, s2);
	return (dest);
}
