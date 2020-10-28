/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <gedemais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:14:53 by gedemais          #+#    #+#             */
/*   Updated: 2019/07/23 06:18:52 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrealloc(char *s, size_t size)
{
	char	*new;

	if (!(new = ft_strnew(size)))
		return (NULL);
	ft_strcpy(new, s);
	ft_strdel(&s);
	return (new);
}
