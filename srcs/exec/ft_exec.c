/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:36:29 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/12 23:59:22 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

/* Function that take the command and send it to find_path
before executing it. */
int	do_command(t_mini *mini)
{
	char	*path;
	char	**tmp;
	char	**token;

	path = NULL;
	tmp = list_to_array(mini->env);
	token = token_to_array(mini->ast->cmd);
	if (mini->ast->cmd != NULL)
		path = find_path(token[0], mini->env);
	if (!path)
	{
		free_aux(&path, &token, &tmp, 1);
		g_status = 127;
		exit(error_handler5(mini, 127, "command not found", 1));
	}
	dup2(mini->fdin, 0);
	dup2(mini->fdout, 1);
	if (execve(path, token, tmp) < 0)
	{
		free_aux(&path, &token, &tmp, 0);
		g_status = 1;
		exit(error_handler7(mini, 1, "execve error", 1));
	}
	free_aux(&path, &token, &tmp, 1);
	exit (0);
}

int	simple_commands(t_mini *m)
{
	pid_t	pid;

	if (checking_redirects(m))
		return (g_status);
	while (m->ast->right)
		m->ast = m->ast->right;
	if (m->ast && (m->ast->type == TEXT || m->ast->type == D_Q || \
				m->ast->type == S_Q) && !is_builtin(m->ast->cmd->token))
	{
		pid = fork();
		if (pid == 0)
			do_command(m);
		signal(SIGINT, not_finish_1);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &g_status, 0);
	}
	else if (m->ast && (m->ast->type == TEXT || m->ast->type == D_Q \
			|| m->ast->type == S_Q) && is_builtin(m->ast->cmd->token))
		exec_builtin(m, 0);
	return (g_status);
}

void	ending_cleaning(t_ast **tree)
{
	while ((*tree)->right)
		*tree = (*tree)->right;
	while (*tree)
	{
		if ((*tree)->type == DOUBLE_IN)
		{
			unlink(".here_doc");
			break ;
		}
		if (!(*tree)->prev)
			break ;
		*tree = (*tree)->prev;
	}
	if ((*tree)->right)
		while ((*tree)->right)
			*tree = (*tree)->right;
}

int	checking_processes(t_mini *mini)
{
	if (!ft_n_pipes(mini->cmd))
	{
		simple_commands(mini);
		while (mini->ast->right)
			mini->ast = mini->ast->right;
		ending_cleaning(&(mini->ast));
		if (WIFEXITED(g_status))
			return (WEXITSTATUS(g_status));
	}
	else
	{
		g_status = doing_pipes(mini);
		return (g_status);
	}
	return (g_status);
}

void	go_minishell(t_mini *mini)
{
	mini->fdin = 0;
	mini->fdout = 1;
	g_status = checking_processes(mini);
}
