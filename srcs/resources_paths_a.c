/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources_paths_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 22:35:58 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 00:22:19 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*sprites_paths_ter(unsigned int index)
{
	static char		*paths[SP_MAX] = {
					"resources/sprites/buttons/yes_on.xpm",
					"resources/sprites/buttons/no_off.xpm",
					"resources/sprites/buttons/no_hover.xpm",
					"resources/sprites/buttons/no_on.xpm",
					"resources/sprites/coins.xpm",
					"resources/sprites/new_wave.xpm",
					"resources/sprites/key.xpm",
					"resources/sprites/campaign/1.xpm",
					"resources/sprites/campaign/2.xpm",
					"resources/sprites/campaign/3.xpm",
					"resources/sprites/campaign/4.xpm",
					"resources/sprites/campaign/5.xpm",
					"resources/sprites/campaign/6.xpm",
					"resources/sprites/campaign/7.xpm",
					"resources/sprites/campaign/8.xpm",
					"resources/sprites/campaign/game_over.xpm",
					"resources/sprites/campaign/victory.xpm"};

	return (paths[index]);
}

char	*sprites_paths_bis(unsigned int index)
{
	static char		*paths[SP_MAX] = {
					"resources/sprites/buttons/SP_CP_BUTTON_2O.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_2C.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_2H.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_2O.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_CREATE_1C.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_CREATE_1H.xpm",
					"resources/sprites/buttons/SP_ME_BUTTON_CREATE_1O.xpm",
					"resources/sprites/buttons/SP_NM_BUTTON_MAPED_2C.xpm",
					"resources/sprites/buttons/SP_NM_BUTTON_MAPED_2H.xpm",
					"resources/sprites/buttons/SP_NM_BUTTON_MAPED_2O.xpm",
					"resources/sprites/ts_background.XPM",
					"resources/sprites/cmp_ts_background.XPM",
					"resources/sprites/map_editor_background.xpm",
					"resources/sprites/me_new_map_background.xpm",
					"resources/sprites/map_editor_menu_title.xpm",
					"resources/sprites/map_editor_new_map_title.xpm",
					"resources/sprites/custom_background.xpm",
					"resources/sprites/hitmarker.xpm",
					"resources/sprites/game_over.xpm",
					"resources/sprites/buttons/yes_off.xpm",
					"resources/sprites/buttons/yes_hover.xpm"};

	return (paths[index]);
}

char	*sprites_paths(unsigned int index)
{
	static char		*paths[SP_MAX] = {
					"resources/sprites/buttons/campaign_clic.xpm",
					"resources/sprites/buttons/campaign_hover.xpm",
					"resources/sprites/buttons/campaign_off.xpm",
					"resources/sprites/buttons/custom_clic.xpm",
					"resources/sprites/buttons/custom_hover.xpm",
					"resources/sprites/buttons/custom_off.xpm",
					"resources/sprites/buttons/map_editor_clic.xpm",
					"resources/sprites/buttons/map_editor_hover.xpm",
					"resources/sprites/buttons/map_editor_off.xpm",
					"resources/sprites/buttons/quit_clic.xpm",
					"resources/sprites/buttons/quit_hover.xpm",
					"resources/sprites/buttons/quit_off.xpm",
"resources/sprites/logo.xpm", "resources/sprites/buttons/SP_CP_BUTTON_1C.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_1H.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_1O.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_2C.xpm",
					"resources/sprites/buttons/SP_CP_BUTTON_2H.xpm"};

	if (index < 18)
		return (paths[index]);
	else if (index >= 18 && index < 39)
		return (sprites_paths_bis(index - 18));
	else
		return (sprites_paths_ter(index - 39));
}
