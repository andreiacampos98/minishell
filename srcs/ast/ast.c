/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:54:19 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 11:56:47 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_ast_aux6(t_mini *mini, t_aux *a)
{
	while (a->ast->i > a->i)
		a->ast = a->ast->right;
	if (a->ast->right == NULL)
	{
		a->ast->right = new_node(a->tk->type, a->i, 0);
		a->ast->right->cmd = ft_tokendup(a->tk);
		a->ast->right->prev = a->ast;
	}
	else
	{
		while (a->ast->left != NULL && a->ast->is_null == 0)
		{
			a->i++;
			a->ast = mini->ast;
			while (a->ast->i > a->i)
				a->ast = a->ast->right;
		}
		a->ast->left = new_node(a->tk->type, a->i, 0);
		a->ast->left->cmd = ft_tokendup(a->tk);
		a->ast->left->prev = a->ast;
	}
}

void	build_ast_aux2(t_mini *mini, t_aux *a)
{
	a->p = 0;
	a->p2 = 0;
	if (a->tk)
	{
		build_ast_aux6(mini, a);
		ft_tokenclear(&a->tk);
		a->tk = NULL;
	}
}

void	build_ast_aux3(t_aux *a)
{
	if (!(a->tk))
		a->tk = ft_tnew(ft_strdup(a->cmd->token), a->cmd->type);
	else
		ft_tadd_b(&(a->tk), ft_tnew(ft_strdup(a->cmd->token), a->cmd->type));
}

void	build_ast_aux4(t_aux *a)
{
	if (!(a->p2))
		a->p2 = 1;
	a->p = 0;
}

int	build_ast(t_mini *mini)
{
	t_aux		a;

	build_ast_aux5(&a, mini);
	if (fill_ast_file(mini))
		return (1);
	while (a.cmd)
	{
		a.i = 1;
		a.ast = mini->ast;
		if ((is_q_text(a.cmd->type)) && !(a.p))
			build_ast_aux3(&a);
		else if (is_ftype(a.cmd->type))
			a.p = 1;
		else if ((is_q_text(a.cmd->type)) && (a.p || a.p2))
			build_ast_aux4(&a);
		else if (a.cmd->type == PIPE)
			build_ast_aux2(mini, &a);
		if (a.cmd->next == NULL)
			break ;
		a.cmd = a.cmd->next;
	}
	if (a.tk)
		build_ast_aux(mini, &a);
	return (0);
}
