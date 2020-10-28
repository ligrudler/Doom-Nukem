/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:25:32 by gedemais          #+#    #+#             */
/*   Updated: 2018/11/08 15:16:48 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (!*alst || !alst)
		return ;
	while (*alst)
	{
		tmp = (*alst);
		del(tmp->content, tmp->content_size);
		*alst = NULL;
		alst = &tmp->next;
		free(tmp);
	}
}
