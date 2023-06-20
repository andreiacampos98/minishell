/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 09:08:52 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 09:51:48 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	error_handler1(int code, char *str, t_mini *mini)
{
	int	i;

	i = 0;
	(void)mini;
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token ", 35);
	g_status = code;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!ft_strncmp(str, "`newline'", 9))
		write(2, "`newline'", 9);
	else
	{
		write(2, "`", 1);
		write(2, &str[i], 1);
		if (mini->cmd)
			ft_tokenclear(&mini->cmd);
	}
	write(2, "\n", 1);
	return (g_status);
}

int	error_handler2(int code, char *str1, char *str2, int as)
{
	write(2, "minishell: ", 11);
	write(1, str1, ft_strlen(str1));
	write(2, ": `", 3);
	write(2, str2, ft_strlen(str2));
	g_status = code;
	if (as == 0)
		write(2, "': No such file or directory\n", 29);
	else if (as == 1)
		write(2, "': not a valid identifier\n", 26);
	else
		write(2, "': not a valid parameter\n", 25);
	return (g_status);
}

int	error_handler3(int code, char *str)
{
	g_status = code;
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
	write(2, "[1]+  Done                    export\n", 37);
	return (g_status);
}

int	error_handler4(int code, t_mini *mini)
{
	g_status = code;
	ft_tokenclear(&mini->cmd);
	write(2, "minishell: ", 11);
	write(2, "Sorry, this minishell does not handle unfinished pipes\n", 55);
	return (g_status);
}

int	error_handler5(t_mini *mini, int code, char *str, int n)
{
	g_status = code;
	write(2, "minishell: ", 11);
	if (mini->ast && mini->ast->type == TEXT && !n)
		write(2, mini->ast->cmd->token, ft_strlen(mini->ast->cmd->token));
	if (!n)
		write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	ft_astclear(&mini->ast, mini);
	ft_tokenclear(&mini->cmd);
	ft_tokenclear(&mini->full_cmd);
	return (g_status);
}
