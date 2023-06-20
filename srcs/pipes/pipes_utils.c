/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:33:24 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/12 22:50:52 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	creating_pipes(t_mini *m)
{
	int	i;

	if (m->pipes)
		free(m->pipes);
	m->pipes = (int *)malloc(sizeof(int) * 2 * m->n_pipes);
	if (!m->pipes)
		return (1);
	i = 0;
	while (i < m->n_pipes)
	{
		if (pipe(m->pipes + (2 * i)) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	child_in(t_mini *mini)
{
	char	*path;
	char	**tmp;
	char	**token;

	path = NULL;
	dup2(mini->fdin, 0);
	dup2(mini->fdout, 1);
	close_fd(mini, mini->pipes);
	tmp = list_to_array(mini->env);
	token = token_to_array(mini->ast->cmd);
	if (mini->ast->cmd != NULL)
		path = find_path(token[0], mini->env);
	if (!path)
	{
		g_status = 127;
		exit(error_handler5(mini, 127, "command not found", 0));
	}
	if (execve(path, token, tmp) < 0)
	{
		free(path);
		g_status = 1;
		exit(error_handler5(mini, 1, "execve error", 0));
	}
	exit (0);
}

int	child_out(t_mini *mini)
{
	char	*path;
	char	**tmp;
	char	**token;

	path = NULL;
	dup2(mini->fdin, 0);
	dup2(mini->fdout, 1);
	close_fd(mini, mini->pipes);
	tmp = list_to_array(mini->env);
	token = token_to_array(mini->ast->cmd);
	if (mini->ast->cmd != NULL)
		path = find_path(token[0], mini->env);
	if (!path)
	{
		g_status = 127;
		exit(error_handler5(mini, 127, "command not found", 0));
	}
	if (execve(path, token, tmp) < 0)
	{
		free(path);
		g_status = 1;
		exit(error_handler5(mini, 1, "execve error", 0));
	}
	exit (0);
}

void	close_fd(t_mini *mini, int *pipes)
{
	int	i;

	i = 0;
	while (i < mini->n_pipes * 2)
	{
		close(pipes[i]);
		i++;
	}
}

void	first_pipes_2(t_mini *m, int i)
{
	if ((m->fdout == m->pipes[2 * i + 1] && i > 0) \
	|| (m->fdout == m->pipes[1] && i == 0))
	{
		m->isbuilt = open(".temp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
		m->fdout = m->isbuilt;
	}
	exec_builtin(m, 1);
}
