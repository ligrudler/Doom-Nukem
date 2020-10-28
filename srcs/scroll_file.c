/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/13 14:22:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				init_scroll_file(t_env *env, char *path, char *extension)
{
	t_scroll	*s;

	s = &env->scroll;
	if (!(s->list = listpath(path, extension)))
		return (-1);
	s->max = ft_tablen(s->list);
	s->d = (t_point){WDT / 3, HGT - HGT / 4};
	s->o = (t_point){WDT / 10, HGT / 4 };
	s->color = 0xB22222;
	s->font = FONT_COOLVETICA;
	s->case_size = 50;
	s->mouse_index = -1;
	s->nb_case = s->d.y / s->case_size - 1;
	if (s->case_size > s->max)
		s->nb_case = s->max;
	s->nb_case = s->nb_case < 1 ? 1 : s->nb_case;
	s->nb_case = s->nb_case > 6 ? 6 : s->nb_case;
	return (0);
}

static void		display_str(t_env *env, t_point police, int i)
{
	t_scroll		*s;
	int				pos;
	int				size;
	t_ttf_config	*conf;

	s = &env->scroll;
	conf = ttf_config();
	conf->size = 20;
	ft_bzero(conf->s, sizeof(unsigned char) * 1024);
	if (s->max == 0)
		ft_strlcpy((char *)conf->s, "No map found!", 13);
	else
	{
		size = s->d.x / (conf->size + 10);
		pos = s->current + i;
		if (pos > s->max - 1)
			pos = pos - s->max;
		ft_strlcpy((char *)conf->s, s->list[pos], size);
		if (s->mouse_index == i && env->events.buttons[BUTTON_LCLIC])
		{
			ft_strdel(&s->s_path);
			s->s_path = ft_strdup(s->list[pos]);
		}
	}
	my_string_put(env, env->mlx.img_data, police, s->font);
}

static void		get_mouse_index(t_env *env, t_point pos, t_point rect_d, int i)
{
	int			mouse_x;
	int			mouse_y;
	t_scroll	*s;

	s = &env->scroll;
	mouse_x = env->events.mouse_pos.x;
	mouse_y = env->events.mouse_pos.y;
	if (mouse_x > pos.x && mouse_x < pos.x + rect_d.x
	&& mouse_y > pos.y && mouse_y < pos.y + rect_d.y)
		s->mouse_index = i;
	else if (mouse_x < s->o.x || mouse_x > s->o.x + s->d.x
	|| mouse_y < s->o.y || mouse_y > s->o.y + s->nb_case * s->case_size)
		s->mouse_index = -1;
}

static void		events_scroll_file(t_env *env)
{
	if (env->scroll.mouse_index > -1)
	{
		if (env->events.buttons[BUTTON_SCROLL_UP])
			++env->scroll.current;
		else if (env->events.buttons[BUTTON_SCROLL_DOWN])
			--env->scroll.current;
	}
}

void			display_file(t_env *env)
{
	int				i;
	t_point			pos;
	t_scroll		*s;

	s = &env->scroll;
	if (s->list == NULL)
		return ;
	s->current = s->current < 0 ? s->max : s->current;
	s->current = s->current > s->max ? 0 : s->current;
	i = -1;
	while (++i < s->nb_case)
	{
		pos = (t_point){s->o.x, s->o.y + i * s->case_size + i};
		get_mouse_index(env, pos, (t_point){s->d.x, s->case_size}, i);
		draw_rectangle(env->mlx.img_data, pos, (t_point){s->d.x, s->case_size},
			s->mouse_index == i ? 0x00ffff : s->color);
		display_str(env, (t_point){pos.x + 10, pos.y + s->case_size - 10}, i);
	}
	if (s->mouse_index == -1)
		ft_strdel(&s->s_path);
	events_scroll_file(env);
}
