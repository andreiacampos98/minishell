/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:33:50 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/13 04:36:43 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// A pipe is a connection between two processes, 
// such that the standard output from one process 
//becomes the standard input of the other process.
//pipe() sends the output of the first execve() as input to the second execve()

// If we call fork after creating a pipe, then the 
// parent and child can communicate via the pipe.

// fork() splits the process in two sub-processes 
// -> parallel, simultaneous, happen at the same time
// it returns 0 for the child process, a non-zero for 
// the parent process, -1 in case of error

//fd[1] is the child process, fd[0] the parent process; 
//the child writes, the parent reads
//Since for something to be read, it must be written first, 
//so cmd1/argv[2] will be executed by the child,
// and cmd2/argv[3] by the parent.

//dup2() swaps our files with stdin and stdout
//It needs a waitpid() at the very beginning to wait for 
//the child to finish her process.

extern int	g_status;

void	close_fds(t_mini *m)
{
	if (m->fdin > 0)
		close(m->fdin);
	if (m->fdout > 1)
		close(m->fdout);
}

void	first_pipes(t_mini *m, int i, int f)
{
	if (!checking_redirects_pipes(m, i))
	{
		if (!i && m->ast->type == PIPE && m->ast->right != NULL)
		{
			while (m->ast->right != NULL)
				m->ast = m->ast->right;
			f = 1;
		}
		first_pipes_aux(i, m);
		if (m->ast && m->ast->cmd && m->ast->cmd->token != NULL \
		&& is_builtin(m->ast->cmd->token))
		{
			if (fork() == 0)
				first_pipes_2(m, i);
		}
		else if (m->ast->cmd && m->ast->cmd->token != NULL && \
		!is_builtin(m->ast->cmd->token))
		{
			if (fork() == 0)
				child_in(m);
		}
		close_fds(m);
	}
	first_pipes_aux2(f, m);
}

void	final_pipe(t_mini *m, pid_t *pid, int i)
{
	m->fdin = 0;
	m->fdout = 1;
	if (!checking_redirects_pipes(m, i))
	{
		if (i != 0 && m->ast->type == PIPE)
			m->ast = m->ast->left;
		final_pipe_aux(m);
		if (m->ast && m->ast->cmd && m->ast->cmd->token != NULL \
		&& is_builtin(m->ast->cmd->token))
		{
			*pid = fork();
			if (*pid == 0)
				exec_builtin(m, 1);
		}
		else if (m->ast && m->ast->cmd && \
		m->ast->cmd->token != NULL && !is_builtin(m->ast->cmd->token))
		{
			*pid = fork();
			if (*pid == 0)
				child_out(m);
		}
		close_fds(m);
	}
}

void	init_varpipes(t_mini *mini, int *i, pid_t *pid)
{
	*i = 0;
	mini->n_pipes = ft_n_pipes(mini->cmd);
	creating_pipes(mini);
	mini->isbuilt = 0;
	*pid = 0;
	while (*i < mini->n_pipes)
	{
		mini->fdin = 0;
		mini->fdout = 1;
		first_pipes(mini, *i, 0);
		(*i)++;
	}
}

int	doing_pipes(t_mini *mini)
{
	int		status;
	int		i;
	pid_t	pid;

	if (mini->ast == NULL)
		return (130);
	init_varpipes(mini, &i, &pid);
	final_pipe(mini, &pid, i);
	close_fd(mini, mini->pipes);
	signal(SIGINT, not_finish_1);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	while (i-- >= 0)
	{
		signal(SIGINT, not_finish_1);
		signal(SIGQUIT, SIG_IGN);
		waitpid(0, NULL, 0);
	}
	deleting_tempfiles(mini->ast);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
