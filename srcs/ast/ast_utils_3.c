/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:40:35 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/10 17:37:48 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_pipes_red(t_token *cmd)
{
	t_token	*aux;

	aux = cmd;
	while (aux)
	{
		if (aux->type == PIPE || is_ftype(aux->type))
			return (1);
		if (aux->next == NULL)
			break ;
		aux = aux->next;
	}
	return (0);
}

int	ft_check_type(t_token *cmd, t_lex_type type)
{
	t_token	*aux;

	aux = cmd;
	while (aux)
	{
		if (aux->type == type)
			return (1);
		if (aux->next == NULL)
			break ;
		aux = aux->next;
	}
	return (0);
}

void	build_1_ast(t_mini *mini)
{
	t_token	*tk;

	tk = mini->cmd;
	mini->ast = new_node(tk->type, 0, 0);
	mini->ast->cmd = ft_tokendup(tk);
}

void	check_nulls_aux(t_mini *mini, int i, int p, int f)
{
	t_ast	*aux;

	aux = mini->ast;
	if (p == 1 && f > 0)
	{
		while (aux->i > (i - f))
			aux = aux->right;
		aux->left = new_node(0, 0, 1);
	}
}

void	check_nulls(t_mini *mini, int i, int p, int f)
{
	t_token	*tk;

	tk = mini->cmd;
	while (tk)
	{
		if (tk->type == PIPE)
		{
			check_nulls_aux(mini, i++, p, f);
			p = 1;
		}
		else if (is_ftype(tk->type))
		{
			f++;
			if (tk->next->type == TEXT || tk->next->type == D_Q || \
					tk->next->type == S_Q)
				tk = tk->next;
			i++;
		}
		else
		{
			f = 0;
			p = 0;
		}
		tk = tk->next;
	}
}
