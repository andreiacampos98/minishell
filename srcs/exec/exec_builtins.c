/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:16:06 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/13 00:05:56 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", ft_strlen(cmd) + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd) + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1) == 0)
		return (1);
	return (0);
}

void	exec_builtin2(t_mini *mini)
{
	if (ft_strncmp(mini->cmd->token, "unset", \
				ft_strlen(mini->ast->cmd->token) + 1) == 0)
		g_status = ft_unset(mini, 0);
	if (ft_strncmp(mini->cmd->token, "exit", \
				ft_strlen(mini->ast->cmd->token) + 1) == 0)
		g_status = ft_exit(mini, mini->ast->cmd);
}

void	exec_builtin(t_mini *mini, int pipes)
{
	if (pipes)
	{
		dup2(mini->fdin, 0);
		dup2(mini->fdout, 1);
		close_fd(mini, mini->pipes);
	}
	if (ft_strncmp(mini->ast->cmd->token, "echo", \
				ft_strlen(mini->ast->cmd->token) + 1) == 0)
		g_status = ft_echo(mini->ast->cmd, mini);
	if (ft_strncmp(mini->cmd->token, "cd", \
				ft_strlen(mini->ast->cmd->token) + 1) == 0)
		g_status = ft_cd(mini->cmd, mini->env);
	if (ft_strncmp(mini->ast->cmd->token, "pwd", \
				ft_strlen(mini->ast->cmd->token) + 1) == 0)
		g_status = ft_pwd(mini);
	if (ft_strncmp(mini->ast->cmd->token, "env", \
				ft_strlen(mini->ast->cmd->token) + 1) == 0)
		g_status = ft_env(mini->env, mini);
	if (ft_strncmp(mini->ast->cmd->token, "export", \
				ft_strlen(mini->ast->cmd->token) + 1) == 0)
		g_status = ft_export(mini, mini->ast->cmd);
	exec_builtin2(mini);
	if (pipes)
		exit(0);
}
