/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grudler <grudler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:57:47 by grudler           #+#    #+#             */
/*   Updated: 2020/05/14 05:20:38 by grudler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCHIVE_H
# define ARCHIVE_H

# define BOUNDARY "=#=#=#=#=#=#=#=#=#=#"
# define ARCHIVE "./resources.archi"

int		free_stuff(void *ptrs[4]);
int		archive_directory(char *dir_path);
int		unarchive_directory(char *archive_path);

#endif
