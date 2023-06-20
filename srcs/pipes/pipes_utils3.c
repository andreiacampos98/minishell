/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 04:35:57 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/13 04:36:51 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_pipes_aux2(int f, t_mini *m)
{
	if (m->ast->prev)
		m->ast = m->ast->prev;
	if (m->ast->prev && !f)
		m->ast = m->ast->prev;
}

void	final_pipe_aux(t_mini *m)
{
	if (m->ast->fdin != -1)
		m->fdin = m->ast->fdin;
	if (m->ast->fdout != -1)
		m->fdout = m->ast->fdout;
	else
		m->fdout = 1;
}
