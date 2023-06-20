/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:44:35 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/12 23:55:47 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer_aux_2(t_mini *mini)
{
	int	i;

	i = 0;
	if (check_redirect(mini->line_read) > 0)
	{
		i = check_redirect(mini->line_read);
		ft_tk_red(mini, 1);
	}
	return (i);
}

void	lexer_aux_3(t_mini *mini)
{
	int		i;
	int		len;
	int		tl;

	len = ft_strlen(mini->line_read);
	i = lexer_aux_2(mini);
	while (i < len)
	{
		if (ft_lexer_aux_1(mini->full_cmd, &mini->line_read[i], 0) != 0)
			tl = ft_lexer_aux_1(mini->full_cmd, &mini->line_read[i], 1);
		else if (ft_lexer_aux_2(&mini->full_cmd, &mini->line_read[i], 0))
			tl = ft_lexer_aux_2(&mini->full_cmd, &mini->line_read[i], 1);
		else if (ft_lexer_aux_3(mini->full_cmd, &mini->line_read[i], 0) != 0)
			tl = ft_lexer_aux_3(mini->full_cmd, &mini->line_read[i], 1);
		else
			tl = ft_lexer_aux_4(&mini->full_cmd, &mini->line_read[i]);
		i += tl;
	}
}

char	*check_seq_reds(t_mini *mini)
{
	t_token	*tk;
	int		f;

	f = 0;
	tk = mini->cmd;
	while (tk)
	{
		if (is_ftype(tk->type))
		{
			if (f)
				return (tk->token);
			else
				f = 1;
		}
		else
			f = 0;
		if (tk->next == NULL)
			break ;
		tk = tk->next;
	}
	return (NULL);
}

int	lexer(t_mini *mini, int i, int tl)
{
	while (i < (int)ft_strlen(mini->line_read))
	{
		if (ft_lexer_aux_1(mini->cmd, &mini->line_read[i], 0) != 0)
			tl = ft_lexer_aux_1(mini->cmd, &mini->line_read[i], 1);
		else if (ft_lexer_aux_2(&mini->cmd, &mini->line_read[i], 0))
			tl = ft_lexer_aux_2(&mini->cmd, &mini->line_read[i], 1);
		else if (ft_lexer_aux_3(mini->cmd, &mini->line_read[i], 0) != 0)
			tl = ft_lexer_aux_3(mini->cmd, &mini->line_read[i], 1);
		else
			tl = ft_lexer_aux_4(&mini->cmd, &mini->line_read[i]);
		i += tl;
	}
	lexer_aux_3(mini);
	if (check_unfinished_pipes(mini))
		return (error_handler4(2, mini));
	if (check_seq_reds(mini) != NULL)
		return (error_handler1(2, check_seq_reds(mini), mini));
	if (check_syntax(mini))
		return (error_handler6(1, mini));
	return (check_red_tokens(mini));
}

int	call_lexer(t_mini *mini)
{
	int		i;

	i = ft_strlen(mini->line_read) - 1;
	while (mini->line_read[i] == ' ' || mini->line_read[i] == '\t')
	{
		if (i == 0)
		{
			free(mini->prompt);
			return (1);
		}
		i--;
	}
	if (mini->line_read[i] == '>' || mini->line_read[i] == '<')
		return (error_handler1(2, "`newline'", mini));
	i = lexer_aux(mini);
	if (i < 0)
		return (error_handler1(2, mini->line_read, mini));
	return (lexer(mini, i, 0));
}
