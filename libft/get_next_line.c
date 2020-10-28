/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:21:30 by gedemais          #+#    #+#             */
/*   Updated: 2019/07/22 03:36:10 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_first_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!(line = ft_strnew(i + 1)))
		return (NULL);
	line[i] = '\0';
	while (--i >= 0)
		line[i] = str[i];
	return (line);
}

static void		ft_trim_line(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	ft_bzero(str, i);
	while (str[i])
	{
		str[j] = str[i + 1];
		i++;
		j++;
	}
}

static char		*ft_strealloc(char *s, size_t size)
{
	char	*new;
	int		i;

	i = 0;
	if (!size || !(new = ft_strnew(size)))
		return (NULL);
	ft_strcpy(new, s);
	free(s);
	return (new);
}

static char		*ft_read(const int fd, char *s)
{
	char		*dest;
	char		tmp[BUFF_SIZE + 1];
	size_t		cycle;
	int			end;
	int			len;

	cycle = 1;
	len = ft_strlen(s);
	if (!(dest = ft_strnew(BUFF_SIZE + len + 1)))
		return (NULL);
	if (s)
		ft_strcat(dest, s);
	else
		s = ft_strnew(1);
	free(s);
	while (!ft_strfind(dest, '\n') && (end = read(fd, tmp, BUFF_SIZE)))
	{
		if (end == -1)
			return (NULL);
		tmp[end] = '\0';
		ft_strcat(dest, tmp);
		dest = ft_strealloc(dest, BUFF_SIZE * (cycle + 1) + len);
		cycle++;
	}
	return (dest);
}

int				get_next_line(const int fd, char **line)
{
	static char		*save[4865] = {NULL};

	if (!line || BUFF_SIZE < 1 || fd < 0 || fd > 4864)
		return (-1);
	if (!save[fd] || save[fd][0] == '\0' || !ft_strfind(save[fd], '\n'))
		if (!(save[fd] = ft_read(fd, save[fd])))
			return (-1);
	if (!save[fd] || save[fd][0] == '\0')
		return (0);
	*line = ft_first_line(save[fd]);
	if (ft_strfind(save[fd], '\n'))
		ft_trim_line(save[fd]);
	else if (!ft_strfind(save[fd], '\n'))
		ft_bzero(save[fd], ft_strlen(save[fd]));
	return (1);
}
