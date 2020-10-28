/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 16:12:34 by grudler           #+#    #+#             */
/*   Updated: 2020/07/18 17:31:13 by grudler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		free_health_string(char *first, char *hp_max)
{
	free(hp_max);
	free(first);
}

static char		*make_health_string(int nb)
{
	char		*hp_max;
	char		*first;
	char		*dest;
	char		*pv;

	if (!(pv = ft_itoa(nb)))
		return (NULL);
	if (!(first = ft_strjoin(pv, "/")))
	{
		free(pv);
		return (NULL);
	}
	free(pv);
	if (!(hp_max = ft_itoa(HP_MAX)))
	{
		free(first);
		return (NULL);
	}
	if (!(dest = ft_strjoin(first, hp_max)))
	{
		free_health_string(first, hp_max);
		return (NULL);
	}
	free_health_string(first, hp_max);
	return (dest);
}

int				draw_health(t_env *env)
{
	t_ttf_config	*conf;
	int				color;
	char			*test;

	conf = ttf_config();
	conf->size = 16;
	if (env->player.hp <= 0)
		env->player.hp = 0;
	if (env->player.hp <= HP_MAX * 1 / 3)
		color = RED_HEALTH;
	else if (env->player.hp > HP_MAX * 2 / 3)
		color = GREEN_HEALTH;
	else
		color = ORA_HEALTH;
	draw_rectangle(env->mlx.img_data, (t_point){0.04 * WDT, 0.9 * HGT},
		(t_point){0.20 * WDT, 20}, NORMAL_BLACK);
	draw_rectangle(env->mlx.img_data, (t_point){0.04 * WDT, 0.9 * HGT},
		(t_point){0.20 * WDT * env->player.hp / HP_MAX, 20}, color);
	if (!(test = make_health_string(env->player.hp)))
		return (-1);
	ft_strcpy((char*)conf->s, test);
	my_string_put(env, env->mlx.img_data, (t_point){0.1 * WDT, 0.9 * HGT + 16},
		FONT_ARIAL);
	free(test);
	return (0);
}
