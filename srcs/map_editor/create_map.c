/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:36:03 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:36:25 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		check_digits(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

static int		get_dimensions(t_env *env)
{
	char		*s[3];
	t_edit_env	*e;
	int			i;

	i = 0;
	e = &env->edit_env;
	s[0] = env->ttfs.fields[FIELD_NM_MAP_WIDTH].str.c;
	s[1] = env->ttfs.fields[FIELD_NM_MAP_HEIGHT].str.c;
	s[2] = env->ttfs.fields[FIELD_NM_MAP_DEPTH].str.c;
	if (check_digits(s[0]) || check_digits(s[1]) || check_digits(s[2]))
		return (CM_ERR_INVALID_DIM);
	e->new_map.width = ft_atoi(s[0]);
	e->new_map.height = ft_atoi(s[1]);
	e->new_map.depth = ft_atoi(s[2]);
	if (!ft_inbounds(e->new_map.width, 1, INT_MAX)
		|| !ft_inbounds(e->new_map.height, 1, INT_MAX)
		|| !ft_inbounds(e->new_map.depth, 1, INT_MAX))
		return (CM_ERR_INVALID_DIM);
	if (e->new_map.width * e->new_map.height * e->new_map.depth > MAX_CHUNKS)
		return (CM_ERR_TOO_MANY_CHUNKS);
	return (0);
}

static int		get_map_name(t_env *env)
{
	char	*input;
	int		i;

	i = 0;
	input = env->ttfs.fields[FIELD_NM_NAME].str.c;
	if (!input || !input[0])
		return (CM_ERR_INVALID_NAME);
	while (input[i])
	{
		if (!ft_isalnum(input[i]))
			return (CM_ERR_INVALID_NAME);
		i++;
	}
	if (!(env->edit_env.new_map.name = ft_strdup(input)))
		return (CM_ERR_INVALID_NAME);
	return (0);
}

int				create_me_map(t_env *env)
{
	int		errcode;

	if ((errcode = get_dimensions(env)))
		return (errcode);
	if ((errcode = get_map_name(env)))
		return (errcode);
	if (build_map(env, &env->edit_env.new_map))
		return (-1);
	return (0);
}
