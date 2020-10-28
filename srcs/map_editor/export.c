/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:51:58 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:51:59 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	write_header(char **str, char *map_name)
{
	char	*tmp;
	char	*tmp2;
	int		magic;

	magic = MAP_MAGIC_NUMBER;
	if (!(tmp = ft_strnew(sizeof(int))))
		return (-1);
	ft_memcpy(tmp, &magic, sizeof(int));
	if (!(tmp2 = ft_strdup(map_name)))
	{
		free(tmp);
		return (-1);
	}
	if (!(*str = ft_strjoin(tmp, tmp2)))
	{
		free(tmp);
		free(tmp2);
		return (-1);
	}
	free(tmp);
	free(tmp2);
	return (0);
}

static void	gen_path(char path[MAX_MAP_PATH_LEN], char *name)
{
	ft_bzero(path, MAX_MAP_PATH_LEN);
	ft_strcpy(path, MAPED_SAVE_PATH);
	ft_strcat(path, name);
	ft_strcat(path, ".map");
}

static char	*add_matrice(t_edit_env *env, char *header, int *len)
{
	char	*file;
	int		matrice_len;
	int		i;

	i = -1;
	if (!flat_map(&env->new_map, &matrice_len))
	{
		free(header);
		return (NULL);
	}
	if (!(file = ft_strnew(*len + matrice_len + sizeof(t_vec3d))))
		return (NULL);
	while (++i < *len)
		file[i] = header[i];
	free(header);
	i = -1;
	while (++i < matrice_len)
		file[i + *len] = env->new_map.flat[i];
	file[i + *len] = 0;
	*len += matrice_len;
	return (file);
}

static int	count_blocks(t_edit_env *env, unsigned char block)
{
	int		ret;
	int		x;
	int		y;
	int		z;

	x = 0;
	ret = 0;
	while (x < env->new_map.width)
	{
		y = 0;
		while (y < env->new_map.height)
		{
			z = 0;
			while (z < env->new_map.depth)
			{
				if (env->new_map.map[x][y][z] == block)
					ret++;
				z++;
			}
			y++;
		}
		x++;
	}
	return (ret);
}

int			export_maped_map(t_edit_env *env)
{
	char	path[MAX_MAP_PATH_LEN];
	char	*header;
	char	*str;
	int		len;

	if (count_blocks(env, 165) != 1)
		return (MAPERR_PLAYER_SPAWNER);
	if (write_header(&header, env->new_map.name))
		return (-1);
	len = ft_strlen(header);
	gen_path(path, env->new_map.name);
	if (!(str = add_matrice(env, header, &len)))
		return (-1);
	if (!write_infile(path, str, len, true))
		return (-1);
	free(str);
	free(env->new_map.flat);
	return (0);
}
