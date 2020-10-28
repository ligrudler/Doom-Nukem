/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_field_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:09:07 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 16:12:45 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char		matcher(int key_id)
{
	static char	chars[NB_KEYS] = {'a', 's', 'd', 'f', 'h', 'g', 'z', 'x', 'c',
									'v', 0, 'b', 'q', 'w', 'e', 'r', 'y', 't',
									'1', '2', '3', '4', '6', '5', '=', '9', '7',
									'-', '8', '0', 0, 'o', 'u', 0, 'i', 'p', 0,
									'l', 'j', 0, 'k', 0, 0, 0, 0, 'n', 'm', 0,
									0, ' '};

	return (key_id > KEY_SPACE ? 0 : chars[key_id]);
}

int			add_char(t_dynarray *txt, bool keys[NB_KEYS])
{
	static bool	l_keys[NB_KEYS];
	char		c;
	int			i;

	i = 0;
	while (i < NB_KEYS)
	{
		if (!l_keys[i] && keys[i] && (c = matcher(i)))
		{
			if (push_dynarray(txt, &c, false))
				return (-1);
			l_keys[i] = true;
		}
		if (!keys[i])
			l_keys[i] = false;
		i++;
	}
	return (0);
}

int			get_boxs(t_ttf *ttfs, t_dynarray *boxs)
{
	void			*tmp;
	unsigned int	i;

	i = 0;
	if (init_dynarray(boxs, sizeof(void*), 0))
		return (-1);
	while (i < FIELD_MAX)
	{
		tmp = &ttfs->fields[i];
		if (ttfs->fields[i].rendered)
			if (push_dynarray(boxs, &tmp, false))
				return (-1);
		i++;
	}
	return (0);
}
