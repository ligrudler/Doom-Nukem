/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:31:26 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:31:33 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		cmp_end(t_env *env)
{
	int		sprite;

	if (env->cmp_env.end_t <= 0 && switch_campaign_subcontext(env, CMP_SC_MENU))
		return (-1);
	if (env->cmp_env.done && env->cmp_env.failed)
		return (-1);
	env->cmp_env.end_t -= env->data.spent;
	sprite = env->cmp_env.failed ? SP_CMP_GAME_OVER : SP_CMP_VICTORY;
	map_sprite(env->mlx.img_data, env->sprites[sprite], (t_point){0, 0});
	mlx_put_image_to_window(env->mlx.mlx_ptr,
		env->mlx.mlx_win, env->mlx.img_ptr, 0, 0);
	return (0);
}
