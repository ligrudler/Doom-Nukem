/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 01:54:42 by maboye            #+#    #+#             */
/*   Updated: 2020/07/18 16:23:39 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum	e_maped_errors
{
	MAPERR_NONE,
	MAPERR_PLAYER_SPAWNER,
	MAPERR_MAX
};

# define MLX_INIT_FAIL "mlx_init() failed\n"
# define MLX_NW_FAIL "mlx_new_window() failed\n"
# define MLX_NI_FAIL "mlx_new_image() failed\n"
# define MLX_GDA_FAIL "mlx_get_data_addr() failed\n"

# define BMP_READER "bmp file reader failed\n"

# define OPEN_DEVICE "alcOpenDevice() failed\n"
# define CREATE_CONTEXT "alcCreateContext() failed\n"
# define CONTEXT_CURRENT "alcMakeContextCurrent() failed\n"
# define SAMPLE_NF " : sample not found\n"

# define NEL_MAP "Wrong number of lines in config file of map "

# define OBJ_LINE_FORMAT "Unexpected line format in obj file : "

# define BMP_HEADER "Wrong path or file format for "

# define ICS_ERR "Illegal context switch. Abort"
# define ISCS_ERR "Illegal sub_context switch. Abort"

# define FT_LIB "FreeType lib initilization failed"

# define NSFD_ERR " : No such file or directory"

# define NO_UVS_ERR "No UVs vertices found for this mesh"

# define ARCHIVE_ERR "archive_directory() failed"
# define UNARCHIVE_ERR "unarchive_directory() failed"

#endif
