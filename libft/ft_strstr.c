/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:29:10 by gedemais          #+#    #+#             */
/*   Updated: 2018/11/06 19:03:53 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(needle);
	if (!len)
		return ((char *)haystack);
	while (haystack[i])
	{
		if (ft_strncmp(&haystack[i], needle, len) == 0)
			return ((char*)&haystack[i]);
		i++;
	}
	return (NULL);
}
