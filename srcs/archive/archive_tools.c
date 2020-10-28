/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 17:39:02 by grudler           #+#    #+#             */
/*   Updated: 2020/07/18 17:31:55 by grudler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		free_stuff(void *ptrs[4])
{
	if (ptrs[0])
		closedir((DIR*)ptrs[0]);
	if (ptrs[1])
		close((int)ptrs[1]);
	if (ptrs[2])
		close((int)ptrs[2]);
	if (ptrs[3])
		free(ptrs[3]);
	return (-1);
}
