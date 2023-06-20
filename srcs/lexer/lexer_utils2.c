/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:29:27 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/12 23:26:36 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tk_red_2(t_mini *mini, int full_cmd)
{
	if (mini->line_read[1] == '>')
	{
		if (full_cmd == 1)
			ft_tadd_b(&mini->full_cmd, ft_tnew(ft_strdup(">>"), DOUBLE_OUT));
		else
			ft_tadd_b(&mini->cmd, ft_tnew(ft_strdup(">>"), DOUBLE_OUT));
	}
	else
	{
		if (full_cmd == 1)
			ft_tadd_b(&mini->full_cmd, ft_tnew(ft_strdup(">"), OUT));
		else
			ft_tadd_b(&mini->cmd, ft_tnew(ft_strdup(">"), OUT));
	}
}

void	ft_tk_red(t_mini *mini, int full_cmd)
{
	if (mini->line_read[0] == '<')
	{
		if (mini->line_read[1] == '<')
		{
			if (full_cmd == 1)
				ft_tadd_b(&mini->full_cmd, ft_tnew(ft_strdup("<<"), DOUBLE_IN));
			else
				ft_tadd_b(&mini->cmd, ft_tnew(ft_strdup("<<"), DOUBLE_IN));
		}
		else
		{
			if (full_cmd == 1)
				ft_tadd_b(&mini->full_cmd, ft_tnew(ft_strdup("<"), IN));
			else
				ft_tadd_b(&mini->cmd, ft_tnew(ft_strdup("<"), IN));
		}
	}
	else if (mini->line_read[0] == '>')
		ft_tk_red_2(mini, full_cmd);
}

int	ft_lexer_aux_1(t_token *t, char *cmds, int is_tadd)
{
	int	token_len;

	token_len = 0;
	if (cmds[0] == '|')
	{
		token_len = 1;
		if (is_tadd == 1)
			ft_tadd_b(&t, ft_tnew(ft_strdup("|"), PIPE));
	}
	else if (cmds[0] == '<')
	{
		token_len = 1;
		if (cmds[1] == '<')
		{
			token_len++;
			if (is_tadd == 1)
				ft_tadd_b(&t, ft_tnew(ft_strdup("<<"), DOUBLE_IN));
		}
		else if (is_tadd == 1)
			ft_tadd_b(&t, ft_tnew(ft_strdup("<"), IN));
	}
	return (token_len);
}

int	ft_n_aspas(char *str, int *i, int n)
{
	int		aa;
	char	c;

	aa = 0;
	c = '0';
	while (str[++(*i)] != '\0')
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			if (aa && str[*i] == c)
			{
				aa = 0;
				n++;
			}
			else if (!aa)
			{
				n++;
				aa = 1;
				c = str[*i];
			}
		}
		else if (str[*i] == ' ' && !aa)
			break ;
	}
	return (n);
}

void	ft_quotes_tk_aux(char **tk, int n, char *str2, int is_malloc)
{
	if (is_malloc)
	{
		if (n % 2 == 0)
			(*tk) = malloc(sizeof(char) * (ft_strlen(str2) - n + 1));
		else
			(*tk) = malloc(sizeof(char) * (ft_strlen(str2) - n + 2));
	}
	else
	{
		if (n % 2 == 0)
			(*tk)[ft_strlen(str2) - n] = '\0';
		else
			(*tk)[ft_strlen(str2) - (n - (n % 2))] = '\0';
	}
}
