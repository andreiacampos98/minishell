/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:23:27 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/12 23:13:14 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quotes_tk(char **tk, char *str, int *i)
{
	t_aux2	*a;

	ft_init_a(&a, str, i);
	if (a->n > 0)
	{
		ft_quotes_tk_aux(tk, a->n, a->s, 1);
		(*i) = -1;
		while (a->s[++(*i)])
			ft_quotes_tk_aux3(&a, (*i), tk);
		ft_quotes_tk_aux(tk, a->n, a->s, 0);
		if (a->c != '0' && a->aa)
			ft_quotes_tk_aux2(a->k, a->c, tk);
		ft_quotes_tk_aux(tk, a->n, a->s, 0);
	}
	else
		(*tk) = ft_strdup(a->s);
	free(a->s);
	free(a);
}

int	ft_lexer_aux_2(t_token **t, char *cmds, int is_tadd)
{
	int		token_len;
	char	*str;
	int		i;

	token_len = 0;
	i = -1;
	if (cmds[0] == '\'')
	{
		ft_quotes_tk(&str, cmds, &i);
		token_len = i;
		if (is_tadd)
			ft_tadd_b(t, ft_tnew(ft_strdup(str), S_Q));
		free(str);
	}
	else if (cmds[0] == '"')
	{
		ft_quotes_tk(&str, cmds, &i);
		token_len = i;
		if (is_tadd)
			ft_tadd_b(t, ft_tnew(ft_strdup(str), D_Q));
		free(str);
	}
	else if (cmds[0] == ' ')
		token_len = 1;
	return (token_len);
}

int	ft_lexer_aux_4(t_token **t, char *cmds)
{
	int		token_len;
	char	*str;
	int		i;

	i = -1;
	ft_quotes_tk(&str, cmds, &i);
	token_len = i;
	ft_tadd_b(t, ft_tnew(ft_strdup(str), TEXT));
	free(str);
	return (token_len);
}

// && (cmds[1] != '\"' || !len))
// && (cmds[1] != '\'' || !len))
