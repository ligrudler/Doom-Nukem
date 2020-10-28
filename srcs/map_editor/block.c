/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:12:59 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/16 22:03:31 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			del_block(t_env *env)
{
	t_mesh	*mesh;
	int		pos[3];

	if (!env->mid.mesh)
		return (0);
	mesh = env->mid.mesh;
	ft_memcpy(pos, mesh->m_pos, sizeof(int) * 3);
	if (pos[1] <= 0)
		return (0);
	mesh->type = BTXT_NONE;
	env->edit_env.new_map.map[pos[0]][pos[1]][pos[2]] = BTXT_NONE;
	if (sound_system(env, SA_TAKE,
		sp_fork(env->sound.volume, PITCH, env->cam.stats.pos)))
		return (-1);
	return (0);
}

void		replace_block(t_env *env)
{
	int		pos[3];
	t_mesh	*mesh;
	int		i;
	char	bt;

	i = -1;
	if (!(mesh = env->mid.mesh))
		return ;
	bt = env->edit_env.current_bt;
	ft_memcpy(pos, mesh->m_pos, sizeof(int) * 3);
	if (env->events.buttons[BUTTON_SCLIC]
		&& env->edit_env.current_bc == BC_CUBE)
		if (env->events.buttons[BUTTON_SCROLL_UP]
			|| env->events.buttons[BUTTON_SCROLL_DOWN])
		{
			mesh->type = bt + 1;
			env->edit_env.new_map.map[pos[0]][pos[1]][pos[2]] = bt + 1;
			while (++i < mesh->tris.nb_cells)
				((t_triangle*)dyacc(&mesh->tris, i))->sp = mesh->type;
		}
}

int			put_block(t_env *env)
{
	t_mesh		*new;
	int			pos[3];
	int			m_index;
	char		bc;

	bc = env->edit_env.current_bc;
	ft_memcpy(pos, &env->mid.mesh->m_pos, sizeof(int) * 3);
	if (replace_by_face(env, pos, env->mid.face_i,
		env->edit_env.new_map.map[pos[0]][pos[1]][pos[2]]))
		return (0);
	new = get_blockindex(&env->edit_env.map, pos, &m_index);
	new->type = env->edit_env.current_bt + 1;
	env->edit_env.new_map.map[pos[0]][pos[1]][pos[2]] = new->type;
	free_dynarray(&new->tris);
	if (bc == BC_CUBE || bc == BC_OBJ)
		create_cube(env, new, new->type);
	else if (ft_inbounds(bc, BC_SLOPE_NORD, BC_SLOPE_EST))
		create_slope(env, new, new->type);
	attribute_mesh(&env->edit_env.map, m_index);
	if (sound_system(env, SA_PUT,
		sp_fork(env->sound.volume, PITCH, env->cam.stats.pos)))
		return (-1);
	return (0);
}
