/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:14:29 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 14:15:01 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	make_ammos_n_slash(t_weapon *w, char **l, char **tmp)
{
	if (!(*l = ft_itoa(w->loaded)))
		return (-1);
	if (!(*tmp = ft_strjoin(*l, ft_strlen(*l) == 1 ? " /" : "/")))
	{
		free(*l);
		return (-1);
	}
	free(*l);
	return (0);
}

static int	make_string(t_weapon *w, unsigned char s[MAX_STR_CHARS])
{
	char	*dest;
	char	*tmp;
	char	*l;
	char	*m;

	if (make_ammos_n_slash(w, &l, &tmp))
		return (-1);
	if (!(m = ft_itoa(w->ammos)))
	{
		free(tmp);
		return (-1);
	}
	if (!(dest = ft_strjoin(tmp, m)))
	{
		free(m);
		free(tmp);
		return (-1);
	}
	free(m);
	free(tmp);
	ft_strcpy((char*)s, dest);
	free(dest);
	return (0);
}

int			print_ammos(t_env *env, t_weapon *w)
{
	t_ttf_config	*conf;

	conf = ttf_config();
	if (make_string(w, conf->s))
		return (-1);
	conf->size = AMMO_FONT_SIZE;
	my_string_put(env, env->mlx.img_data, (t_point){900, 670}, FONT_AMMOS);
	conf->size = W_NAME_FONT_SIZE;
	ft_strcpy((char*)conf->s, w->name);
	my_string_put(env, env->mlx.img_data, (t_point){900, 630}, FONT_ARIAL);
	return (0);
}
