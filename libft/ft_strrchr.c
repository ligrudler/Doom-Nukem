/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:28:52 by gedemais          #+#    #+#             */
/*   Updated: 2018/11/05 17:28:54 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	if (c == 0)
		return ((char*)&s[ft_strlen(s)]);
	while (i > 0)
	{
		i--;
		if (s[i] == (unsigned char)c)
			return ((char*)&s[i]);
	}
	return (NULL);
}
