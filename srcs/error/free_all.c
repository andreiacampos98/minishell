/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 09:39:33 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/12 21:30:24 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_astclear_prev(t_ast *ast)
{
	t_ast	*aux;

	while (ast && ast->prev)
	{
		aux = ast->prev;
		ft_tokenclear(&ast->left->cmd);
		free(ast->left);
		free(ast);
		ast = aux;
	}
	if (ast)
	{
		ft_tokenclear(&ast->left->cmd);
		free(ast->left);
		free(ast);
	}
}

void	ft_astclear_next(t_ast *ast)
{
	t_ast	*aux;
	int		i;

	while (ast && ast->right)
	{
		aux = ast->right;
		ft_tokenclear(&ast->left->cmd);
		free(ast->left);
		i = ast->i;
		free(ast);
		ast = aux;
	}
	if (ast && i == 1 && ast->i == 1)
	{
		ft_tokenclear(&ast->cmd);
		free(ast);
	}
}

void	ft_astclear_ast(t_ast **ast, t_mini *mini)
{
	if (!(*ast)->right && !(*ast)->left)
		(*ast) = (*ast)->prev;
	if ((*ast)->i < mini->n_tk && (*ast)->prev)
		ft_astclear_prev((*ast)->prev);
	if ((*ast)->i > 1 && (*ast)->right)
		ft_astclear_next((*ast)->right);
	if ((*ast))
	{
		if ((*ast)->left)
		{
			ft_tokenclear(&(*ast)->left->cmd);
			free((*ast)->left);
		}
		if ((*ast)->right && (*ast)->i == 1 && (*ast)->right->i == 1)
		{
			ft_tokenclear(&(*ast)->right->cmd);
			free((*ast)->right);
		}
		if ((*ast)->cmd)
			ft_tokenclear(&(*ast)->cmd);
		free((*ast));
	}
}

void	ft_astclear_1ast(t_ast **ast)
{
	if ((*ast))
	{
		ft_tokenclear(&(*ast)->cmd);
		free(*ast);
	}
}

void	ft_astclear(t_ast **ast, t_mini *mini)
{
	if (mini->ast_active)
	{
		if (mini->no_ast == 1)
			ft_astclear_1ast(ast);
		else
			ft_astclear_ast(ast, mini);
		mini->ast_active = 0;
		mini->i_exec = 1;
		mini->fill_fds = 0;
	}
}
