/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:54:03 by grudler           #+#    #+#             */
/*   Updated: 2020/07/22 18:10:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char			*strcat_path(char *s1, char *s2, char *s3)
{
	ft_strcat(s1, s2);
	ft_strcat(s1, "/");
	ft_strcat(s1, s3);
	return (s1);
}

static int			concat_files(char *path, int fd_archi)
{
	int		fd_file;
	int		len;
	char	*contain;

	write(fd_archi, BOUNDARY, ft_strlen(BOUNDARY));
	write(fd_archi, "\n", 1);
	write(fd_archi, path, ft_strlen(path));
	write(fd_archi, "\n", 1);
	if ((fd_file = open(path, O_RDONLY)) < 0)
		return (-1);
	if (!(contain = read_file(fd_file, &len)))
		return (free_stuff((void*[4]){NULL, NULL, &fd_file, NULL}));
	close(fd_file);
	unlink(path);
	if (len)
	{
		write(fd_archi, contain, len);
		write(fd_archi, "\n", 1);
	}
	munmap(contain, len);
	return (0);
}

static int			read_folder(char *dir_path, int fd_archi)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*path;

	errno = 0;
	if (!(dir = opendir(dir_path)))
		return (-1);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (!(path = ft_strnew(ft_strlen(dir_path) + dirent->d_namlen + 2)))
			return (free_stuff((void*[4]){dir, &fd_archi, NULL, NULL}));
		strcat_path(path, dir_path, dirent->d_name);
		if ((dirent->d_type == DT_REG) && (*dirent->d_name == '.'))
			unlink(path);
		else if (dirent->d_type == DT_REG && concat_files(path, fd_archi))
			return (free_stuff((void*[4]){dir, &fd_archi, NULL, path}));
		else if (dirent->d_type == DT_DIR && (*dirent->d_name != '.'))
		{
			read_folder(path, fd_archi);
			rmdir(path);
		}
		free(path);
	}
	closedir(dir);
	return (errno == 0 ? 0 : -1);
}

int					archive_directory(char *dir_path)
{
	int	fd_archi;

	if ((fd_archi = open(ARCHIVE, O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
	{
		perror(strerror(errno));
		return (-1);
	}
	if (read_folder(dir_path, fd_archi))
		return (-1);
	close(fd_archi);
	rmdir(dir_path);
	return (0);
}
