/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:59:50 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 13:22:48 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer_aux(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->line_read[i] == ' ' || mini->line_read[i] == '\t')
		i++;
	if (mini->line_read[i] == '|')
		return (-1);
	else if (check_redirect(mini->line_read) > 0)
	{
		i = check_redirect(mini->line_read);
		ft_tk_red(mini, 0);
	}
	return (i);
}

int	check_redirect(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '<')
	{
		i = 1;
		if (str[1] == '<')
			i = 2;
	}
	else if (str[0] == '>')
	{
		i = 1;
		if (str[1] == '>')
			i = 2;
	}
	return (i);
}

void	ft_quotes_tk_aux2(int k, char c, char **tk)
{
	int	j;

	j = -1;
	if (k < (int)ft_strlen(*tk))
	{
		while (((int)ft_strlen(*tk) - ++j) > k)
			(*tk)[(int)ft_strlen(*tk) - j] = (*tk)[(int)ft_strlen(*tk) - 1 - j];
	}
	(*tk)[k] = c;
}

void	ft_init_a(t_aux2 **a, char *str, int *i)
{
	(*a) = malloc(sizeof(t_aux2));
	(*a)->aa = 0;
	(*a)->c = '0';
	(*a)->j = 0;
	(*a)->k = -1;
	(*a)->n = ft_n_aspas(str, i, 0);
	if ((*a)->n > 0)
		(*a)->s = ft_substr(str, 0, (*i));
	else
	{
		(*i) = ft_sl2(str);
		(*a)->s = ft_substr(str, 0, (*i));
	}
}

void	ft_quotes_tk_aux3(t_aux2 **a, int i, char **tk)
{
	if (((*a)->s[i] == '\"' || (*a)->s[i] == '\'') && \
			((*a)->s[i] == (*a)->c || (*a)->c == '0'))
	{
		if ((*a)->aa && (*a)->s[i] == (*a)->c)
		{
			(*a)->aa = 0;
			(*a)->c = '0';
		}
		else
		{
			(*a)->k = (*a)->j;
			(*a)->aa = 1;
			(*a)->c = (*a)->s[i];
		}
	}
	else
		(*tk)[(*a)->j++] = (*a)->s[i];
}
