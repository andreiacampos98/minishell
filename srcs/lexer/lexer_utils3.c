/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:04:48 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/12 23:16:47 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_red_tokens(t_mini *mini)
{
	t_token	*tk;

	tk = mini->cmd;
	while (tk)
	{
		if (is_ftype(tk->type) && tk->next == NULL)
			return (error_handler1(2, "`newline'", mini));
		if (tk->next == NULL)
			break ;
		tk = tk->next;
	}
	return (0);
}

int	ft_sl2(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != ' ' && str[i] != '|' && \
			str[i] != '<' && str[i] != '>' && str[i])
		i++;
	return (i);
}

int	check_unfinished_pipes(t_mini *mini)
{
	t_token	*tk;

	tk = mini->cmd;
	while (tk)
	{
		if (tk->next == NULL && tk->type == PIPE)
			return (1);
		tk = tk->next;
	}
	return (0);
}

int	check_syntax(t_mini	*mini)
{
	t_token	*tk;
	int		f;

	tk = mini->cmd;
	f = 0;
	while (tk)
	{
		if (tk->type == TEXT || tk->type == D_Q || tk->type == S_Q)
			f = 1;
		else if (tk->type == PIPE)
		{
			if (!f)
				return (1);
			f = 0;
		}
		if (tk->next == NULL)
			break ;
		tk = tk->next;
	}
	return (0);
}

int	ft_lexer_aux_3(t_token *t, char *cmds, int is_tadd)
{
	int	token_len;

	token_len = 0;
	if (cmds[0] == '>')
	{
		token_len = 1;
		if (cmds[1] == '>')
		{
			token_len++;
			if (is_tadd == 1)
				ft_tadd_b(&t, ft_tnew(ft_strdup(">>"), DOUBLE_OUT));
		}
		else if (is_tadd == 1)
			ft_tadd_b(&t, ft_tnew(ft_strdup(">"), OUT));
	}
	return (token_len);
}
