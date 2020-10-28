/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:29:00 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/21 17:20:35 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_sep(char c, char *charset)
{
	int i;

	i = 0;
	if (!(c))
		return (1);
	while (charset[i])
		if (charset[i++] == c)
			return (1);
	return (0);
}

char	*ft_strdup_sep(char *src, char *charset)
{
	char	*dest;
	int		i;

	i = 0;
	while (!(is_sep(src[i], charset)))
		i++;
	if (!(dest = (char *)malloc(sizeof(*dest) * (i + 1))))
		return (0);
	i = 0;
	while (!(is_sep(src[i], charset)))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		c_w(char *str, char *charset)
{
	int words;
	int i;

	i = 0;
	words = 1;
	while (str[i])
	{
		if (is_sep(str[i], charset) && !(is_sep(str[i + 1], charset)))
			words++;
		i++;
	}
	return (words);
}

char	**ft_strsplit(char *str, char *charset)
{
	char	**tab;
	int		words;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(str) || !(charset))
		return (NULL);
	words = c_w(str, charset);
	if (!(tab = (char**)malloc(sizeof(char*) * (words + 2))))
		return (NULL);
	while (j < words)
	{
		while (is_sep(str[i], charset))
			i++;
		if (!(tab[j] = ft_strdup_sep(&str[i], charset)))
			return (NULL);
		while (!(is_sep(str[i], charset)))
			i++;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
