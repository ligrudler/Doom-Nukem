/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:13:17 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/14 16:23:17 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	**tab_add(char **tab, const char *str)
{
	int		i;
	int		error;
	char	**ret;

	error = 0;
	if (tab == NULL || str == NULL)
		error = 1;
	if (error == 1
			|| !(ret = (char **)ft_memalloc(sizeof(char *)
					* (ft_tablen(tab) + 2))))
		error = 1;
	i = -1;
	while (error == 0 && tab[++i])
		if (!(ret[i] = ft_strdup(tab[i])))
			error = 1;
	if (error == 1 || !(ret[i] = ft_strdup(str)))
		error = 1;
	if (error == 1)
		ft_free_ctab(ret);
	else
		ret[++i] = NULL;
	ft_free_ctab(tab);
	return (ret);
}

static int	good_format(char *str, char *format)
{
	int			len;

	len = ft_strlen(format);
	while (len--)
		if (!ft_isalnum(format[len]) && !(format[len] == '.'))
			return (0);
	return (!ft_strcmp(str, format) ? 1 : 0);
}

static int	check_format(char ***path_tab, struct dirent *r, char *format)
{
	int size;

	size = ft_strlen(r->d_name);
	while (size > 0 && r->d_name[size] != '.')
		--size;
	if (size == 0)
		return (0);
	if (good_format(r->d_name + size, format) == 1)
	{
		while (--size > -1)
			if (!ft_isalnum(r->d_name[size]))
				return (0);
		if (!(*path_tab = tab_add(*path_tab, r->d_name)))
			return (-1);
		return (1);
	}
	return (0);
}

char		**listpath(char *d_path, char *format)
{
	char			**path_tab;
	DIR				*dir;
	struct dirent	*read;

	path_tab = NULL;
	dir = opendir(d_path);
	if (dir)
	{
		if (!(path_tab = (char **)ft_memalloc(sizeof(char *) * 1)))
			return (NULL);
		while ((read = readdir(dir)))
			if (check_format(&path_tab, read, format) == -1)
				break ;
		closedir(dir);
	}
	return (path_tab);
}
