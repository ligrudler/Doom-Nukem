/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:52:17 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 15:53:32 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*read_file(int fd, int *len)
{
	struct stat	file_stat;
	char		*dest;
	int			size;

	if (fstat(fd, &file_stat))
		return (NULL);
	size = file_stat.st_size;
	*len = size;
	if (!(dest = mmap(NULL, (size_t)size,
		PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0)))
		return (NULL);
	return (dest);
}

int		write_infile(char *f_path, char *str, int len, bool token)
{
	int		file;

	if (token)
		unlink(f_path);
	file = open(f_path, O_CREAT | O_WRONLY, 0666);
	if (file > 0)
	{
		write(file, str, len);
		close(file);
		return (1);
	}
	return (0);
}
