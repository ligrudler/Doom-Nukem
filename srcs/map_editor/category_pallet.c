/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   category_pallet.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:19:42 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:20:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	draw_cg_box(t_env *env, t_point o, t_point dims, unsigned int index)
{
	t_point	top_o;
	t_point	top_dims;

	top_o = o;
	top_dims = (t_point){dims.x, 3};
	draw_rectangle(env->mlx.img_data, top_o, top_dims, CG_COLOR);
	if (index == (unsigned int)env->edit_env.current_bc)
	{
		top_o.y += 3;
		draw_rectangle(env->mlx.img_data, top_o, dims, 0x00aa00);
	}
}

static void	render_category(t_env *env, t_point o, char *s)
{
	t_ttf_config	*conf;
	unsigned char	*str;

	conf = ttf_config();
	conf->size = 14;
	str = (unsigned char*)s;
	ft_bzero(conf->s, MAX_STR_CHARS);
	ft_memcpy(conf->s, str, ft_strlen(s));
	my_string_put(env, env->mlx.img_data, o, FONT_ARIAL);
	ft_bzero(conf->s, MAX_STR_CHARS);
}

static void	draw_top_n_bottom(t_env *env, t_point o, t_point dims, t_point v)
{
	draw_rectangle(env->mlx.img_data,
			(t_point){o.x - 3, o.y}, (t_point){dims.x + 3, 3}, CG_COLOR);
	o.y -= (dims.y * BC_MAX);
	draw_rectangle(env->mlx.img_data, o, (t_point){dims.x, 3}, 0xffffff);
	draw_rectangle(env->mlx.img_data, (t_point){o.x - 3, o.y}, v, CG_COLOR);
	draw_rectangle(env->mlx.img_data,
		(t_point){o.x + dims.x - 3, o.y}, v, CG_COLOR);
}

void		draw_cg_pallet(t_env *env)
{
	static char		*strings[BC_MAX] = {"cube", "pente est", "pente ouest",
										"pente nord", "pente sud", "gameplay"};
	t_point			dims;
	t_point			o;
	t_point			v;
	unsigned int	i;

	i = 0;
	o = (t_point){930, 20};
	dims = (t_point){130, 30};
	v = (t_point){3, dims.y * BC_MAX};
	while (i < BC_MAX)
	{
		draw_cg_box(env, o, dims, i);
		render_category(env, (t_point){o.x + 5, o.y + dims.y - 5}, strings[i]);
		o.y += dims.y;
		i++;
	}
	draw_top_n_bottom(env, o, dims, v);
}
