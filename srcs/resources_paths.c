/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:53:49 by maboye            #+#    #+#             */
/*   Updated: 2020/07/21 22:56:35 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*maps_paths(unsigned int index)
{
	static char	*paths[SCENE_MAX] = {	"resources/maps/famas.obj",
			"resources/maps/ak47.obj", "resources/maps/sawed-off.obj",
			"resources/maps/glock-18.obj", "resources/maps/aug.obj",
			"resources/maps/ump45.obj", "resources/maps/mag-7.obj",
										"resources/maps/galil.obj",
										"resources/maps/negev.obj",
										"resources/maps/tec-9.obj",
										"resources/maps/physic.obj",
										"resources/maps/cube.obj",
										"resources/maps/axis.obj",
										"resources/maps/pente_nord.obj",
										"resources/maps/pente_ouest.obj",
										"resources/maps/pente_sud.obj",
										"resources/maps/pente_est.obj",
										"resources/maps/map-test.obj",
										"resources/maps/ugly.obj",
										"resources/maps/moon.obj",
										"resources/maps/star.obj",
										"resources/maps/mage.obj",
										"resources/maps/loot.obj",
										"resources/maps/goule.obj",
										"resources/maps/start_room.obj",
										"resources/maps/dust.obj"};

	return (paths[index]);
}

char	*blocs_txt_paths(unsigned int index)
{
	static char		*paths[BTXT_MAX] = {"",
		"resources/textures/blocs/brique.xpm",
		"resources/textures/blocs/brique_dark.xpm",
		"resources/textures/blocs/clean_stone.xpm",
"resources/textures/blocs/dirt.xpm", "resources/textures/blocs/dirt_grass.xpm",
"resources/textures/blocs/dirt_snow.xpm", "resources/textures/blocs/glace.xpm",
"resources/textures/blocs/gold.xpm", "resources/textures/blocs/iron.xpm",
"resources/textures/blocs/light.xpm", "resources/textures/blocs/obsidienne.xpm",
		"resources/textures/blocs/sand.xpm",
		"resources/textures/blocs/stone.xpm",
		"resources/textures/blocs/wood_a.xpm",
		"resources/textures/blocs/wood_a_cut.xpm",
		"resources/textures/blocs/wood_b.xpm",
		"resources/textures/blocs/wood_b_cut.xpm",
		"resources/textures/blocs/wood_c.xpm",
		"resources/textures/blocs/wood_c_cut.xpm",
		"resources/textures/blocs/wood_d.xpm",
		"resources/textures/blocs/wood_d_cut.xpm",
		"resources/textures/blocs/jukebox.xpm",
		"resources/textures/blocs/mystery_box.xpm",
"resources/textures/blocs/door.xpm", "resources/textures/blocs/lava.xpm",
		"resources/textures/blocs/spawner.xpm",
		"resources/textures/blocs/mob_spawner.xpm"};

	return (paths[index]);
}

char	*icones_paths(unsigned int index)
{
	static char		*paths[BTXT_MAX] = {"brick_ico.xpm", "dark_brick_ico.xpm",
										"clean_stone_ico.xpm", "dirt_ico.xpm",
										"dirt_grass_ico.xpm",
										"dirt_snow_ico.xpm", "glace_ico.xpm",
										"gold_ico.xpm",
										"iron_ico.xpm",
										"light_ico.xpm",
										"obsidienne_ico.xpm",
										"sand_ico.xpm",
										"stone_ico.xpm",
										"wood_a_ico.xpm",
										"wood_a_cut_ico.xpm",
										"wood_b_ico.xpm",
										"wood_b_cut_ico.xpm",
										"wood_c_ico.xpm",
										"wood_c_cut_ico.xpm",
										"wood_d_ico.xpm",
										"wood_d_cut_ico.xpm",
										"jukebox_ico.xpm",
										"mystery_box_ico.xpm",
										"door_ico.xpm", "lava_ico.xpm",
										"spawner_ico.xpm",
										"mob_spawner_ico.xpm"};

	return (paths[index]);
}

char	*fonts_paths(unsigned int index)
{
	static char		*paths[FONT_MAX] = {"resources/fonts/arial.ttf",
										"resources/fonts/ammos.ttf",
										"resources/fonts/Courier.dfont",
										"resources/fonts/coolvetica.ttf"};

	return (paths[index]);
}
