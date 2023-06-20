/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:35:15 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/11 09:51:54 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	error_handler(char *str, t_mini *mini, int code)
{
	(void) mini;
	g_status = code;
	write(2, str, ft_strlen(str));
	return (g_status);
}

int	error_handler6(int code, t_mini *mini)
{
	g_status = code;
	write(2, "minishell: syntax error\n", 24);
	ft_tokenclear(&mini->cmd);
	return (g_status);
}

int	error_handler7(t_mini *mini, int code, char *str, int n)
{
	g_status = code;
	write(2, "minishell: ", 11);
	if (mini->ast && mini->ast->type == TEXT && !n)
		write(2, mini->ast->cmd->token, ft_strlen(mini->ast->cmd->token));
	if (!n)
		write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	if (!mini->no_ast)
		ft_astclear(&mini->ast, mini);
	else
		free(mini->ast);
	ft_tokenclear(&mini->cmd);
	ft_tokenclear(&mini->full_cmd);
	return (g_status);
}
