/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources_paths_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 22:56:22 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:11:56 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*samples_paths_bis(unsigned int index)
{
	static char		*paths[SA_MAX] = {
					"resources/samples/weapons/mag7-reload.wav",
					"resources/samples/weapons/mag7-shot.wav",
					"resources/samples/weapons/negev-reload.wav",
					"resources/samples/weapons/negev-shot.wav",
					"resources/samples/weapons/sawed-off-fill.wav",
					"resources/samples/weapons/sawed-off-pump.wav",
					"resources/samples/weapons/sawed-off-shot.wav",
					"resources/samples/weapons/tec9-reload.wav",
					"resources/samples/weapons/tec9-shot.wav",
					"resources/samples/weapons/ump45-reload.wav",
					"resources/samples/weapons/ump45-shot.wav",
					"resources/samples/voices/doublekill.wav",
					"resources/samples/voices/triplekill.wav",
					"resources/samples/voices/rampage.wav",
					"resources/samples/voices/godlike.wav",
					"resources/samples/voices/wickedsick.wav",
					"resources/samples/monsters/death_monster.wav",
					"resources/samples/monsters/levitation.wav",
					"resources/samples/world/button.wav",
					"resources/samples/world/put.wav",
					"resources/samples/world/take.wav"};

	return (paths[index]);
}

char	*samples_paths_ter(unsigned int index)
{
	static char		*paths[SA_MAX] = {
					"resources/samples/world/step.wav",
					"resources/samples/world/lava.wav",
					"resources/samples/world/door.wav",
					"resources/samples/world/change.wav",
					"resources/samples/loots/nuke.wav",
					"resources/samples/loots/ammos.wav",
					"resources/samples/loots/cash.wav",
					"resources/samples/loots/god_end.wav",
					"resources/samples/loots/god_start.wav",
					"resources/samples/voices/player_damage.wav",
					"resources/samples/intro_music.wav",
					"resources/samples/snow.wav",
					"resources/samples/campaign/door.wav",
					"resources/samples/campaign/button.wav",
					"resources/samples/campaign/beep.wav",
					"resources/samples/campaign/boom.wav"};

	return (paths[index]);
}

char	*samples_paths(unsigned int index)
{
	static char		*paths[SA_MAX] = {
					"resources/samples/ambiances/title_screen_intro.wav",
					"resources/samples/ambiances/title_screen_loop.wav",
"resources/samples/musics/game1.wav", "resources/samples/musics/game2.wav",
					"resources/samples/musics/game3.wav",
					"resources/samples/musics/game4.wav",
					"resources/samples/musics/gameover.wav",
					"resources/samples/musics/maped.wav",
					"resources/samples/weapons/ak47-reload.wav",
					"resources/samples/weapons/ak47-shot.wav",
					"resources/samples/weapons/aug-reload.wav",
					"resources/samples/weapons/aug-shot.wav",
					"resources/samples/weapons/famas-reload.wav",
					"resources/samples/weapons/famas-shot.wav",
					"resources/samples/weapons/galil-reload.wav",
					"resources/samples/weapons/galil-shot.wav",
					"resources/samples/weapons/glock-reload.wav",
					"resources/samples/weapons/glock-shot.wav"};

	if (index < 18)
		return (paths[index]);
	else if (index >= 18 && index < 39)
		return (samples_paths_bis(index - 18));
	else
		return (samples_paths_ter(index - 39));
}
