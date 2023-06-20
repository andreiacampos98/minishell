/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:13:05 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/13 23:03:00 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	heredoc(t_mini *mini)
{
	char	*buf;

	buf = NULL;
	while (1)
	{
		signal(SIGINT, not_finish_1);
		signal(SIGQUIT, SIG_IGN);
		buf = readline(">");
		if (buf == NULL)
			break ;
		if (!ft_strncmp(buf, mini->ast->left->cmd->token, \
					ft_strlen(mini->ast->left->cmd->token) + 1))
			break ;
		expand_var(&buf, mini, -1, NULL);
		write(mini->fdin, buf, ft_strlen(buf));
		write(mini->fdin, "\n", 1);
		free(buf);
	}
	free(buf);
	mini->ast->left->here_doc_done = true;
}

int	input(t_mini *mini)
{
	if (mini->ast->left->here_doc_done)
		return (0);
	if (mini->ast->type == IN)
		mini->fdin = open(mini->ast->left->cmd->token, O_RDONLY);
	else
		mini->fdin = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (mini->fdin < 0)
		return (error_handler(": no such file or directory\n", mini, 1));
	if (mini->ast->type == DOUBLE_IN)
	{
		heredoc(mini);
		mini->fdin = open(".here_doc", O_RDONLY);
		if (mini->fdin < 0)
			return (error_handler(": no such file or directory\n", \
						mini, 1));
	}
	return (0);
}

int	output(t_mini *mini)
{
	if (mini->ast->type == OUT)
		mini->fdout = open(mini->ast->left->cmd->token, \
				O_CREAT | O_TRUNC | O_RDWR, 0000666);
	else
		mini->fdout = \
		open(mini->ast->left->cmd->token, O_APPEND | O_CREAT | O_RDWR, 0000666);
	if (mini->fdout < 0)
		return (error_handler(": no such file or directory\n", mini, 1));
	return (0);
}

int	checking_redirects(t_mini *mini)
{
	while (mini->ast->i <= mini->n_tk)
	{
		if (mini->ast->type == IN || mini->ast->type == DOUBLE_IN)
			g_status = input(mini);
		else if (mini->ast->type == OUT || mini->ast->type == DOUBLE_OUT)
			g_status = output(mini);
		else if (mini->ast->type == PIPE || mini->ast->type == TEXT)
			break ;
		if (!mini->ast->prev)
			break ;
		if (g_status != 0)
			return (g_status);
		mini->ast = mini->ast->prev;
	}
	return (0);
}
