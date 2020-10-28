/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:50:02 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/22 15:30:39 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			exit_doom(t_env *env, char *msg, int fd, int code)
{
	if (msg)
		ft_putendl_fd(msg, fd);
	free_env(env);
	if (sound_system(env, -1, sp_stop()))
		return (-1);
	if (archive_directory("./resources"))
	{
		ft_putendl_fd(ARCHIVE_ERR, 2);
		exit(EXIT_FAILURE);
	}
	exit(code);
}

static int	doom_nukem(t_env *env)
{
	srand(time(NULL));
	if (setup(env))
		exit_doom(env, "error", 2, -1);
	env->context = C_TITLE_SCREEN;
	env->scene = 0;
	mlx_mouse_move(env->mlx.mlx_win, WDT / 2, HGT / 2);
	mlx_do_key_autorepeatoff(env->mlx.mlx_ptr);
	mlx_hooks(env);
	return (0);
}

int			main(void)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(t_env));
	if (doom_nukem(&env))
		exit_doom(&env, "Error\n", 2, EXIT_FAILURE);
	exit_doom(&env, NULL, 0, EXIT_SUCCESS);
	return (0);
}
