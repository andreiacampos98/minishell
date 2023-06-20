/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:34:48 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 20:06:14 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ast_firstnode(t_mini *mini)
{
	while (mini->ast->i > 1)
		mini->ast = mini->ast->right;
}

void	call_ast(t_mini *mini)
{
	if (ft_check_pipes_red(mini->cmd))
	{
		build_ast(mini);
		mini->no_ast = 0;
		mini->n_tk = mini->ast->n_tk;
		mini->ast_active = 1;
		ast_firstnode(mini);
	}
	else
	{
		build_1_ast(mini);
		mini->no_ast = 1;
		mini->n_tk = 1;
		mini->ast_active = 1;
	}
}
