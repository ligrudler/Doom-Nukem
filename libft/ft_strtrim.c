/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:30:47 by gedemais          #+#    #+#             */
/*   Updated: 2018/11/07 15:09:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	while (ft_is_whitespace(s[i]))
		i++;
	if (!s[i])
		return (ft_strdup(""));
	while (j > 0 && ft_is_whitespace(s[j]))
		j--;
	if (!(dest = (char*)malloc(sizeof(char) * (j - i) + 1)))
		return (NULL);
	return (ft_strsub(s, i, (j - i) + 1));
}
