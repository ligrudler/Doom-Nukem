/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 16:13:21 by grudler           #+#    #+#             */
/*   Updated: 2020/07/09 15:17:08 by grudler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# include "main.h"
# define HP_MAX 100

/*
**	Height and width for compass components
*/

# define COMP_HGT 35
# define IND_WDT 4
# define EN_WDT 2
# define EN_HGT 15

/*
** Offset y for compass components
*/

# define OFF_CORD 60
# define OFF_EN 45

/*
** Colors for hud
*/

# define DARK_GREY 0x293133
# define LIGHT_GREY 0x9C9C9C
# define NORMAL_RED 0xFF0000
# define RED_HEALTH 0xA50016
# define GREEN_HEALTH 0x009242
# define ORA_HEALTH 0xF88F23
# define NORMAL_BLACK 0x000000

struct	s_hud
{
	long timephysic;
	long timewave;
};

int		draw_hud(t_env *env);
int		draw_health(t_env *env);
void	draw_compass(t_env *env);
int		draw_physic(t_env *env);

#endif
