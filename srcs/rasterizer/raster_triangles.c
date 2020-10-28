/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_triangles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 02:08:49 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/15 13:28:09 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	launch_thread(t_env *env, t_rasthread *thread, int p, int rest)
{
	thread->env = env;
	thread->tris = &env->cam.to_raster;
	thread->start = thread->id * p;
	thread->index = thread->start;
	thread->end = thread->start + p + (thread->id == NB_THREADS - 1 ? rest : 0);
	thread->mono = false;
	if (pthread_create(&thread->thread, NULL, rasthreader, thread))
		return (-1);
	return (0);
}

static int	switch_threads(t_env *env, t_rasthread threads[NB_THREADS],
														int work_size, bool w)
{
	unsigned int	i;
	int				rest;

	i = 0;
	rest = work_size % NB_THREADS;
	while (i < NB_THREADS && i < (unsigned)work_size)
	{
		if (w)
		{
			if (pthread_join(threads[i].thread, NULL))
				return (-1);
		}
		else
		{
			threads[i].id = (int)i;
			if (launch_thread(env, &threads[i], work_size / NB_THREADS, rest))
				return (-1);
		}
		i++;
	}
	return (0);
}

int			raster_triangles(t_env *env, t_dynarray *arr)
{
	t_rasthread	threads[NB_THREADS];

	if (clip_mesh_triangles(arr, &env->cam.to_raster, env->cam.clip_arrs))
		return (-1);
	if (env->cam.to_raster.nb_cells < NB_THREADS)
		monothread_raster(env);
	else
	{
		if (switch_threads(env, threads, env->cam.to_raster.nb_cells, false)
			|| switch_threads(env, threads, env->cam.to_raster.nb_cells, true))
			return (-1);
	}
	clear_dynarray(&env->cam.to_raster);
	clear_dynarray(&env->cam.to_clip);
	return (0);
}
