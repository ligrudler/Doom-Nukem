/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:53:58 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:53:59 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	gen_path(char path[MAX_MAP_PATH_LEN], char *name)
{
	ft_bzero(path, MAX_MAP_PATH_LEN);
	ft_strcpy(path, MAPED_SAVE_PATH);
	ft_strcat(path, name);
}

static int	check_header(char *file, char *name, int file_size, int *len)
{
	int		magic;

	if (ft_strlen(file) <= 4)
		return (-1);
	magic = *(int*)file;
	if (magic != MAP_MAGIC_NUMBER)
	{
		munmap(file, file_size);
		return (-1);
	}
	if (ft_strncmp(&file[sizeof(int)], name, ft_strclen(name, '.')))
	{
		munmap(file, file_size);
		return (-1);
	}
	*len = 4 + ft_strclen(name, '.');
	return (0);
}

static char	*get_file_name(char *name)
{
	char	*dest;
	int		len;

	len = 0;
	while (name[len] && name[len] != '.')
		len++;
	if (!(dest = ft_strnew(len)))
		return (NULL);
	ft_memcpy(dest, name, len);
	return (dest);
}

static int	handle_file(t_edit_env *env, char *name, char p[MAX_MAP_PATH_LEN])
{
	int		fd;

	if (!(env->new_map.name = get_file_name(name)))
		return (-1);
	gen_path(p, name);
	if ((fd = open(p, O_RDONLY)) == -1)
	{
		perror(strerror(errno));
		free(env->new_map.name);
		return (-1);
	}
	return (fd);
}

int			import_maped_map(t_edit_env *env, char *name)
{
	char	path[MAX_MAP_PATH_LEN];
	char	*file;
	int		len;
	int		offset;
	int		fd;

	if ((fd = handle_file(env, name, path)) < 0)
		return (-1);
	if (!(file = read_file(fd, &len)) || len < 6)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (check_header(file, name, len, &offset))
		return (-1);
	env->new_map.flat = (unsigned char*)file;
	if (!flat_to_matrice(&env->new_map, offset, len))
		return (-1);
	munmap(file, len);
	return (0);
}
