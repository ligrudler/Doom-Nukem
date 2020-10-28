/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 17:24:36 by grudler           #+#    #+#             */
/*   Updated: 2020/07/18 17:25:01 by grudler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		animate_position(t_point *pos, float time)
{
	if (time > 5.5f || time < 1.5f)
		pos->x += 15;
	else
		pos->x++;
}

int				print_countdown(t_env *env, float time)
{
	t_ttf_config	*conf;
	static t_point	pos = {-100, 300};
	char			*second;
	int				sec;

	if (time > 6 || time <= 0)
	{
		pos = (t_point){-100, 300};
		return (0);
	}
	sec = floor(time);
	conf = ttf_config();
	conf->size = 24;
	ft_bzero((char*)&conf->s[0], MAX_STR_CHARS);
	ft_strcat((char*)&conf->s[0], "Next Wave in ");
	if (!(second = ft_itoa(sec)))
		return (-1);
	ft_strcat((char*)conf->s, second);
	free(second);
	animate_position(&pos, time);
	my_string_put(env, env->mlx.img_data, pos, FONT_COOLVETICA);
	return (0);
}

int				draw_wave(t_env *env)
{
	t_ttf_config	*conf;
	char			*str;
	char			*s;

	conf = ttf_config();
	conf->size = 20;
	if (!(s = ft_itoa(env->custom_env.game.wave)))
		return (-1);
	if (!(str = ft_strjoin("Wave ", s)))
	{
		free(s);
		return (-1);
	}
	free(s);
	ft_strcpy((char*)conf->s, str);
	free(str);
	my_string_put(env, env->mlx.img_data, (t_point){42, 642}, FONT_COOLVETICA);
	return (0);
}
