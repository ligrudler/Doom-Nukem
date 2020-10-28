/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:15:25 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 14:07:11 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			custom_menu_to_play(t_env *env)
{
	static bool	first = true;
	t_map		*map;

	env->custom_env.spawn_jump = 5;
	map = &env->edit_env.map;
	if (sound_system(env, 0, sp_overall(0, SA_MAX, sp_stop()))
		|| map_to_scene(env) || parse_events_blocks(env)
		|| init_dynarray(&env->custom_env.mobs, sizeof(t_enemy), MAX_ENEMIES)
		|| astar_init(env) || init_map_physics(&env->edit_env.map)
		|| (init_cameras_mesh(map, &map->cam)) || init_sky(env)
		|| init_loots(env) || sound_system(env, SA_BUTTON,
			sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		return (-1);
	set_game_stats(env);
	if (first)
		replace_weapons(env);
	env->data.wireframe = false;
	first = false;
	mlx_mouse_hide();
	env->phy_env.type_move = true;
	env->cam.stats.onfloor = 0;
	env->cam.stats.onroof = 0;
	env->cam.stats.onwall = 0;
	return (0);
}

int			custom_play_to_menu(t_env *env)
{
	if (sound_system(env, 0, sp_overall(0, SA_MAX, sp_stop())))
		return (-1);
	mlx_mouse_show();
	ft_strdel(&env->custom_env.map_path);
	free_maped(env);
	free_dynarray(&env->player.weapons);
	free_dynarray(&env->custom_env.mobs);
	free_dynarray(&env->custom_env.events);
	free_dynarray(&env->astar.d_nodes);
	free_dynarray(&env->astar.d_astar);
	env->custom_env.loot.m = NULL;
	env->phy_env.type_move = false;
	return (0);
}

int			custom_play_to_game_over(t_env *env)
{
	if (sound_system(env, 0, sp_overall(0, SA_MAX, sp_stop())))
		return (-1);
	mlx_mouse_show();
	free_maped(env);
	free_dynarray(&env->player.weapons);
	free_dynarray(&env->custom_env.mobs);
	free_dynarray(&env->custom_env.events);
	free_dynarray(&env->astar.d_nodes);
	free_dynarray(&env->astar.d_astar);
	env->custom_env.loot.m = NULL;
	return (0);
}

int			custom_game_over_to_play(t_env *env)
{
	t_map	*map;

	env->custom_env.spawn_jump = 5;
	if (sound_system(env, 0, sp_overall(0, SA_MAX, sp_stop())))
		return (-1);
	if (sound_system(env, SA_BUTTON,
		sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		return (-1);
	map = &env->edit_env.map;
	if (import_maped_map(&env->edit_env, env->custom_env.map_path)
		|| map_to_scene(env) || parse_events_blocks(env)
		|| init_dynarray(&env->custom_env.mobs, sizeof(t_enemy), MAX_ENEMIES)
		|| astar_init(env) || init_map_physics(&env->edit_env.map)
		|| (init_cameras_mesh(map, &map->cam)) || init_sky(env)
		|| init_loots(env))
		return (-1);
	replace_weapons(env);
	set_game_stats(env);
	env->data.wireframe = false;
	mlx_mouse_hide();
	env->phy_env.type_move = true;
	return (0);
}

int			custom_game_over_to_menu(t_env *env)
{
	if (sound_system(env, 0, sp_overall(0, SA_MAX, sp_stop())))
		return (-1);
	if (sound_system(env, SA_BUTTON,
		sp_play(env->sound.volume * 2, PITCH, env->cam.stats.pos)))
		return (-1);
	free(env->custom_env.map_path);
	env->phy_env.type_move = false;
	return (0);
}
