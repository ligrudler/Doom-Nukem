/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pallet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:25:42 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 17:26:16 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	draw_focus_square(t_env *env, t_point pos, t_point o, int index)
{
	pos = (t_point){o.x + (index * 34) - 1, o.y};
	draw_rectangle(env->mlx.img_data, pos, (t_point){3, 34}, 0x00ff00);
	draw_rectangle(env->mlx.img_data, pos, (t_point){34, 2}, 0x00ff00);
	pos.x += 34;
	draw_rectangle(env->mlx.img_data, pos, (t_point){3, 34}, 0x00ff00);
	pos.x -= 34;
	pos.y += 34;
	draw_rectangle(env->mlx.img_data, pos, (t_point){37, 2}, 0x00ff00);
}

static void	render_obj_name(t_env *env)
{
	static char		*names[NB_INTERACTIVES] = {"Jukebox", "Weapons Chest",
							"Door", "Lava", "Player Spawner", "Mob Spawner"};
	int				index;
	t_ttf_config	*conf;
	t_point			o;

	conf = ttf_config();
	conf->size = 14;
	index = env->edit_env.current_bt - 160;
	o = (t_point){500, 580};
	ft_strcpy((char*)conf->s, names[index]);
	my_string_put(env, env->mlx.img_data, o, FONT_COOLVETICA);
}

void		render_pallet(t_env *env, t_cube_pallet *p, t_point o, char bc)
{
	unsigned int	i;
	t_point			pos;
	int				index;

	i = 0;
	pos = o;
	pos.x += 2;
	pos.y += 2;
	index = env->edit_env.current_bt % 32;
	while (i < BTXT_MAX - 1)
	{
		(void)bc;
		if ((bc == BC_CUBE && p[i].cube)
			|| (ft_inbounds(bc, BC_SLOPE_NORD, BC_SLOPE_EST) && p[i].slope)
			|| (bc == BC_OBJ && p[i].obj))
		{
			blit_sprite(env->mlx.img_data, p[i].sprite, pos, 2.0f);
			pos.x += 34;
		}
		if (bc == BC_OBJ && p[i].obj)
			render_obj_name(env);
		i++;
	}
	draw_focus_square(env, pos, o, index);
}
