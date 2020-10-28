/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_bt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:44:40 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 17:52:11 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		*bt_arrays(int index)
{
	static int	arrays[3][128];
	static bool	first = true;
	int			i;

	i = 0;
	if (first)
	{
		while (++i < NB_CUBES_ICONES)
			arrays[0][i] = i;
		while (++i < 128 + NB_CUBES_ICONES)
			arrays[1][i] = i;
	}
	first = false;
	return (arrays[index]);
}

static void		switch_cube_type(unsigned char *bt, t_events *e)
{
	static int	bt_cube = 0;
	int			*ptr;

	ptr = bt_arrays(0);
	if (e->buttons[BUTTON_SCROLL_UP])
		bt_cube = (bt_cube >= NB_CUBES_ICONES) ? 0 : bt_cube + 1;
	else if (e->buttons[BUTTON_SCROLL_DOWN])
		bt_cube = (bt_cube <= 0) ? NB_CUBES_ICONES - 1 : bt_cube - 1;
	*bt = (unsigned char)ptr[bt_cube];
}

static void		switch_slope_type(unsigned char bc, unsigned char *bt,
																	t_events *e)
{
	static int				bt_s = 0;
	static unsigned char	last_bc = 0;
	int						*ptr;
	int						start;

	ptr = bt_arrays(1);
	if (bt_s == 0 || last_bc != bc)
		bt_s = bc * 32;
	if (bc == BC_SLOPE_NORD)
		start = 32;
	else if (bc == BC_SLOPE_SUD)
		start = 64;
	else if (bc == BC_SLOPE_OUEST)
		start = 96;
	else if (bc == BC_SLOPE_EST)
		start = 128;
	else
		return ;
	if (e->buttons[BUTTON_SCROLL_UP])
		bt_s = (bt_s >= start + NB_CUBES_ICONES - 1) ? start : bt_s + 1;
	else if (e->buttons[BUTTON_SCROLL_DOWN])
		bt_s = (bt_s < start) ? start + NB_CUBES_ICONES - 1 : bt_s - 1;
	*bt = (unsigned char)ptr[bt_s];
	last_bc = bc;
}

static void		switch_obj_type(unsigned char *bt, t_events *e)
{
	if (e->buttons[BUTTON_SCROLL_UP])
		*bt = (*bt >= 160 + NB_INTERACTIVES - 1) ? 160 : *bt + 1;
	else if (e->buttons[BUTTON_SCROLL_DOWN])
		*bt = (*bt <= 160) ? 160 + NB_INTERACTIVES - 1 : *bt - 1;
}

void			switch_block_type(t_env *env, t_events *e)
{
	unsigned char	*bt;
	unsigned char	bc;

	bc = env->edit_env.current_bc;
	bt = &env->edit_env.current_bt;
	if (bc == BC_CUBE)
		switch_cube_type(bt, e);
	else if (ft_inbounds(bc, BC_SLOPE_NORD, BC_SLOPE_EST))
		switch_slope_type(bc, bt, e);
	else if (bc == BC_OBJ)
		switch_obj_type(bt, e);
}
