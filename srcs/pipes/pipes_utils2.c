/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:21:18 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/12 22:49:30 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	get_input(t_mini *mini, int i, int max)
{
	int	in;

	if (i == 0)
		in = 0;
	else if (i == max - 1)
		in = mini->pipes[mini->n_pipes * 2 - 2];
	else
		in = mini->pipes[2 * i - 2];
	if (mini->isbuilt != 0)
	{
		close(mini->isbuilt);
		in = open(".temp", O_RDONLY);
		mini->isbuilt = 0;
	}
	return (in);
}

int	get_output(t_mini *mini, int i, int max)
{
	int	out;

	if (i == 0)
		out = mini->pipes[1];
	else if (i == max -1)
		out = 1;
	else
		out = mini->pipes[2 * i + 1];
	return (out);
}

int	checking_redirects_pipes(t_mini *mini, int i)
{
	(void)i;
	while (mini->ast->i < mini->i_exec)
		mini->ast = mini->ast->prev;
	if (count_red(mini->cmd) > 0 && mini->fill_fds == 0)
	{
		fill_fds(mini->ast, mini->n_tk);
		mini->fill_fds = 1;
	}
	if (checking_redirects(mini))
		return (g_status);
	mini->i_exec = mini->ast->i;
	if (mini->fdin == 0)
		mini->fdin = get_input(mini, i, mini->n_pipes + 1);
	if (mini->fdout == 1)
		mini->fdout = get_output(mini, i, mini->n_pipes + 1);
	return (0);
}

void	deleting_tempfiles(t_ast *t)
{
	while (t && t->right)
		t = t->right;
	while (t)
	{
		if (t->type == DOUBLE_IN)
			unlink(".here_doc");
		if (t->type == TEXT && is_builtin(t->cmd->token))
			unlink(".temp");
		else if (t->left && t->left->type == TEXT && \
		is_builtin(t->left->cmd->token))
			unlink(".temp");
		if (!t->right)
			break ;
		t = t->right;
	}
}

void	first_pipes_aux(int i, t_mini *m)
{
	if (i != 0 && m->ast->type == PIPE)
		m->ast = m->ast->left;
	if (m->ast && m->ast->fdin != -1)
		m->fdin = m->ast->fdin;
	if (m->ast && m->ast->fdout != -1)
		m->fdout = m->ast->fdout;
}
