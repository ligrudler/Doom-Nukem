/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:28:43 by gedemais          #+#    #+#             */
/*   Updated: 2018/11/16 09:01:57 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;
	int		i;

	i = 0;
	if (!needle[0])
		return ((char*)haystack);
	n = ft_strlen(needle);
	if (n == 1 && ft_strlen(haystack) == 1)
		return ((char*)haystack);
	while (haystack[i] != '\0' && (len >= n))
	{
		if (ft_strncmp(&haystack[i], needle, n) == 0)
			return ((char*)&haystack[i]);
		len--;
		i++;
	}
	return (NULL);
}
