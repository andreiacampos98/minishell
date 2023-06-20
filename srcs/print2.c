/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 09:53:29 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 09:29:27 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	ft_type(t_lex_type type)
{
	if (type == PIPE)
		return ('|');
	else if (type == IN)
		return ('<');
	else if (type == OUT)
		return ('>');
	else if (type == DOUBLE_IN)
		return ('I');
	else if (type == DOUBLE_OUT)
		return ('O');
	else if (type == T_FILE)
		return ('F');
	else if (type == S_Q)
		return ('S');
	else if (type == D_Q)
		return ('D');
	else
		return ('T');
}

void	ft_astprintrev(t_mini *mini)
{
	t_ast	*ta;

	ft_printf("------------------------AST-----------------------\n");
	ta = mini->ast;
	if (!mini->no_ast)
	{
		while (ta->prev)
		{
			ta = ta->prev;
			ft_printf("NODE: %d - type: %c\n", ta->i, ft_type(ta->type));
			if (ta->right != NULL && ta->i == 1)
				astprint_aux(ta);
			if (ta->left != NULL)
				astprint_aux2(ta);
		}
	}
	else
		ft_printf("AST 1  type: %c ; cmd: ", ft_type(ta->left->type));
}
