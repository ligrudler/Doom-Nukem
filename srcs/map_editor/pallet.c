/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pallet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:45:06 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 16:51:53 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	set_renderable(t_cube_pallet p[BTXT_MAX])
{
	t_cube_pallet	pallet;
	int				i;

	i = 0;
	pallet = (t_cube_pallet){.cube = 1, .slope = 1, .obj = 0};
	while (i < BTXT_JUKEBOX)
	{
		ft_memcpy(&p[i], &pallet, sizeof(t_cube_pallet));
		i++;
	}
	p[BTXT_JUKEBOX - 1] = (t_cube_pallet){.cube = 0, .slope = 0, .obj = 1};
	p[BTXT_MYSTERY_BOX - 1] = (t_cube_pallet){.cube = 0, .slope = 0, .obj = 1};
	p[BTXT_DOOR - 1] = (t_cube_pallet){.cube = 0, .slope = 0, .obj = 1};
	p[BTXT_LAVA - 1] = (t_cube_pallet){.cube = 0, .slope = 0, .obj = 1};
	p[BTXT_SPAWNER - 1] = (t_cube_pallet){.cube = 0, .slope = 0, .obj = 1};
	p[BTXT_MOB_SPAWNER - 1] = (t_cube_pallet){.cube = 0, .slope = 0, .obj = 1};
}

static int	count_icones(t_cube_pallet *p, char bc)
{
	unsigned int	i;
	int				ret;

	i = 0;
	ret = 0;
	while (i < BTXT_MAX)
	{
		if (bc == BC_CUBE && p[i].cube)
			ret++;
		else if (ft_inbounds(bc, BC_SLOPE_NORD, BC_SLOPE_EST) && p[i].slope)
			ret++;
		else if (bc == BC_OBJ && p[i].obj)
			ret++;
		i++;
	}
	return (ret);
}

static void	draw_pallet_bbox(t_env *env, t_point *origin, char bc)
{
	t_point	o;
	t_point	dims;
	t_point	s_dims;
	int		offset;
	int		nb_icones;

	if (!(nb_icones = count_icones(env->edit_env.pallet, bc)))
		return ;
	offset = nb_icones * 34;
	o = (t_point){env->data.half_wdt - (offset / 2), 600};
	*origin = o;
	dims = (t_point){offset, 2};
	s_dims = (t_point){2, 34};
	draw_rectangle(env->mlx.img_data, o, dims, 0xffffff);
	draw_rectangle(env->mlx.img_data, o, s_dims, 0xffffff);
	o.x += offset;
	draw_rectangle(env->mlx.img_data, o, s_dims, 0xffffff);
	o.x -= offset;
	dims.x += 2;
	o.y += s_dims.y;
	draw_rectangle(env->mlx.img_data, o, dims, 0xffffff);
}

int			render_pallets(t_env *env)
{
	t_point		o;
	char		bc;

	bc = env->edit_env.current_bc;
	draw_pallet_bbox(env, &o, bc);
	render_pallet(env, env->edit_env.pallet, o, bc);
	return (0);
}

int			init_cubes_pallet(t_env *env, t_edit_env *edit_env)
{
	char			path[256];
	unsigned int	i;

	i = 0;
	set_renderable(edit_env->pallet);
	while (i < BTXT_MAX - 1)
	{
		ft_strcpy(path, MAPED_ICONE_PATH);
		ft_strcat(path, icones_paths(i));
		if (load_texture(&env->mlx, path,
				&edit_env->pallet[i].sprite, false))
			return (-1);
		i++;
	}
	return (0);
}
