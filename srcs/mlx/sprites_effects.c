/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_effects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 21:23:04 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/08 21:23:14 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	mirror_texture(t_sprite *txt)
{
	int		i;
	int		j;
	int		k;
	int		pixel;

	i = 0;
	while (i < txt->hgt)
	{
		j = i * txt->wdt * 4;
		k = j + (txt->wdt * 4) - 4;
		while (j < k)
		{
			pixel = *(int*)&txt->img_data[j];
			ft_memcpy(&txt->img_data[j], &txt->img_data[k], 4);
			ft_memcpy(&txt->img_data[k], &pixel, 4);
			j += 4;
			k -= 4;
		}
		i++;
	}
}

void		reverse_texture(t_sprite *txt)
{
	int		i;
	int		j;
	int		pixel;
	int		data_size;

	data_size = txt->hgt * txt->wdt * 4;
	i = 0;
	j = data_size - 4;
	while (i < j)
	{
		pixel = *(int*)&txt->img_data[i];
		ft_memcpy(&txt->img_data[i], &txt->img_data[j], 4);
		ft_memcpy(&txt->img_data[j], &pixel, 4);
		i += 4;
		j -= 4;
	}
	mirror_texture(txt);
}
