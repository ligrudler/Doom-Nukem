/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:50:56 by gedemais          #+#    #+#             */
/*   Updated: 2020/07/09 21:50:58 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_states_a(char states[PS_MAX][PS_MAX])
{
	states[PS_OBJ][PS_OBJ] = 0;
	states[PS_OBJ][PS_VERTEXS] = 1;
	states[PS_OBJ][PS_END_VERTEXS] = 0;
	states[PS_OBJ][PS_FACES] = 0;
	states[PS_OBJ][PS_COMMENT] = 1;
	states[PS_OBJ][PS_MTLLIB] = 0;
	states[PS_OBJ][PS_USEMTL] = 0;
	states[PS_VERTEXS][PS_OBJ] = 0;
	states[PS_VERTEXS][PS_VERTEXS] = 1;
	states[PS_VERTEXS][PS_TXT_VERTEXS] = 1;
	states[PS_VERTEXS][PS_END_VERTEXS] = 1;
	states[PS_VERTEXS][PS_FACES] = 0;
	states[PS_VERTEXS][PS_COMMENT] = 1;
	states[PS_VERTEXS][PS_MTLLIB] = 0;
	states[PS_VERTEXS][PS_USEMTL] = 1;
	states[PS_END_VERTEXS][PS_OBJ] = 0;
	states[PS_END_VERTEXS][PS_VERTEXS] = 0;
	states[PS_END_VERTEXS][PS_TXT_VERTEXS] = 0;
	states[PS_END_VERTEXS][PS_END_VERTEXS] = 0;
	states[PS_END_VERTEXS][PS_FACES] = 1;
	states[PS_END_VERTEXS][PS_COMMENT] = 1;
	states[PS_END_VERTEXS][PS_MTLLIB] = 0;
	states[PS_END_VERTEXS][PS_USEMTL] = 0;
}

static void	init_states_b(char states[PS_MAX][PS_MAX])
{
	states[PS_TXT_VERTEXS][PS_OBJ] = 0;
	states[PS_TXT_VERTEXS][PS_VERTEXS] = 1;
	states[PS_TXT_VERTEXS][PS_TXT_VERTEXS] = 1;
	states[PS_TXT_VERTEXS][PS_END_VERTEXS] = 1;
	states[PS_TXT_VERTEXS][PS_FACES] = 0;
	states[PS_TXT_VERTEXS][PS_COMMENT] = 1;
	states[PS_TXT_VERTEXS][PS_MTLLIB] = 0;
	states[PS_TXT_VERTEXS][PS_USEMTL] = 1;
	states[PS_FACES][PS_OBJ] = 1;
	states[PS_FACES][PS_VERTEXS] = 0;
	states[PS_FACES][PS_TXT_VERTEXS] = 1;
	states[PS_FACES][PS_END_VERTEXS] = 1;
	states[PS_FACES][PS_FACES] = 1;
	states[PS_FACES][PS_COMMENT] = 1;
	states[PS_FACES][PS_MTLLIB] = 0;
	states[PS_FACES][PS_USEMTL] = 1;
	ft_memset(&states[PS_COMMENT], 1, sizeof(char) * PS_MAX);
	states[PS_MTLLIB][PS_OBJ] = 1;
	states[PS_MTLLIB][PS_VERTEXS] = 0;
	states[PS_MTLLIB][PS_TXT_VERTEXS] = 0;
	states[PS_MTLLIB][PS_END_VERTEXS] = 0;
	states[PS_MTLLIB][PS_FACES] = 1;
	states[PS_MTLLIB][PS_COMMENT] = 1;
	states[PS_MTLLIB][PS_MTLLIB] = 1;
	states[PS_MTLLIB][PS_USEMTL] = 0;
}

static void	init_states_c(char states[PS_MAX][PS_MAX])
{
	states[PS_USEMTL][PS_OBJ] = 0;
	states[PS_USEMTL][PS_VERTEXS] = 0;
	states[PS_USEMTL][PS_TXT_VERTEXS] = 0;
	states[PS_USEMTL][PS_END_VERTEXS] = 1;
	states[PS_USEMTL][PS_FACES] = 1;
	states[PS_USEMTL][PS_COMMENT] = 1;
	states[PS_USEMTL][PS_MTLLIB] = 0;
	states[PS_USEMTL][PS_USEMTL] = 0;
}

void		init_states(char states[PS_MAX][PS_MAX])
{
	init_states_a(states);
	init_states_b(states);
	init_states_c(states);
}
