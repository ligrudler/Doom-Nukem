/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:08:47 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 16:11:59 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			render_field(t_env *env, void *addr)
{
	t_ttf_config	*conf;
	t_point			name_pos;
	t_text_box		*box;
	unsigned char	*s;

	ft_memcpy(&box, addr, sizeof(void*));
	conf = ttf_config();
	conf->size = 20;
	ft_memset(conf->s, 0, sizeof(char) * MAX_STR_CHARS);
	ft_strcpy((char*)conf->s, box->name);
	name_pos = (t_point){box->o.x + 50, box->o.y};
	my_string_put(env, env->mlx.img_data, name_pos, FONT_ARIAL);
	box->b_o = (t_point){box->o.x, box->o.y + conf->size};
	draw_rectangle(env->mlx.img_data, box->b_o,
		(t_point){TEXT_BOX_DIMSX, TEXT_BOX_DIMSY}, TEXT_BOX_COLOR);
	ft_memset(conf->s, 0, sizeof(char) * MAX_STR_CHARS);
	s = (unsigned char *)box->str.c;
	s[box->str.nb_cells] = 0;
	ft_strcpy((char*)conf->s, box->str.c);
	my_string_put(env, env->mlx.img_data,
		(t_point){box->b_o.x, box->b_o.y + conf->size}, FONT_ARIAL);
	ft_memset(conf->s, 0, sizeof(char) * MAX_STR_CHARS);
}

static t_text_box	*get_current_box(t_dynarray *boxs)
{
	t_text_box	*box;
	void		*tmp;
	int			i;

	i = 0;
	while (i < boxs->nb_cells)
	{
		tmp = dyacc(boxs, i);
		ft_memcpy(&box, tmp, sizeof(void*));
		if (box->in)
			return (box);
		i++;
	}
	return (NULL);
}

static void			refresh_in(t_env *env, t_dynarray *boxs)
{
	t_text_box	*box;
	void		*tmp;
	t_point		mp;
	int			i;

	i = 0;
	mp = env->events.mouse_pos;
	while (i < boxs->nb_cells)
	{
		tmp = dyacc(boxs, i);
		ft_memcpy(&box, tmp, sizeof(void*));
		if (ft_inbounds(mp.x, box->b_o.x, box->b_o.x + TEXT_BOX_DIMSX)
			&& ft_inbounds(mp.y, box->b_o.y, box->b_o.y + TEXT_BOX_DIMSY))
			box->in = true;
		else
			box->in = false;
		i++;
	}
}

static int			field_content(t_env *env, t_text_box *box)
{
	static bool		del = true;
	t_point			c_o;

	if (env->events.keys[KEY_BACKSPACE] && del)
	{
		del = false;
		return (pop_dynarray(&box->str, false));
	}
	if (!env->events.keys[KEY_BACKSPACE])
		del = true;
	if (ft_strlen((char*)box->str.c) >= 12)
		return (0);
	if (add_char(&box->str, env->events.keys))
		return (-1);
	c_o = (t_point){box->b_o.x + (box->str.nb_cells * 17) + 3, box->b_o.y + 2};
	draw_rectangle(env->mlx.img_data, c_o, (t_point){1, 26}, CURSOR_COLOR);
	return (0);
}

int					input_fields(t_env *env, bool refresh, bool free)
{
	static t_dynarray	boxs;
	t_text_box			*current;
	static bool			first = true;
	int					i;

	i = 0;
	if ((refresh || first) && get_boxs(&env->ttfs, &boxs))
		return (-1);
	if (free && !first)
	{
		free_dynarray(&boxs);
		return (0);
	}
	while (i < boxs.nb_cells)
	{
		render_field(env, dyacc(&boxs, i));
		i++;
	}
	first = false;
	if (env->events.buttons[BUTTON_LCLIC])
		refresh_in(env, &boxs);
	if (!(current = get_current_box(&boxs)))
		return (0);
	field_content(env, current);
	return (0);
}
