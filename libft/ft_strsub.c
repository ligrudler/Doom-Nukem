/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:30:32 by gedemais          #+#    #+#             */
/*   Updated: 2018/11/08 20:07:13 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!s || (start == 0 && len == ft_strlen(s) - 1))
		return ((char*)s);
	if ((start == 0 && len == 0) || len <= 0)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		return (NULL);
	if (!(dest = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
