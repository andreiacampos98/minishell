/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:32:04 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/10 17:35:46 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*new_node(t_lex_type type, int i, int in)
{
	t_ast	*new;

	new = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new)
		return (0);
	new->i = i;
	new->type = type;
	new->cmd = NULL;
	new->n_tk = 0;
	new->left = NULL;
	new->right = NULL;
	new->prev = NULL;
	new->is_null = in;
	new->fdin = -1;
	new->fdout = -1;
	return (new);
}

void	add_node_to_ast(t_mini *mini, t_ast *node)
{
	if (mini->ast == NULL || node == NULL)
		return ;
	node->right = mini->ast;
	mini->ast->prev = node;
	mini->ast = node;
}

int	is_ftype(t_lex_type type)
{
	if (type == IN || type == OUT || type == DOUBLE_IN || type == DOUBLE_OUT)
		return (1);
	return (0);
}

int	build_ast_base(t_mini *mini)
{
	t_token	*tmp;
	int		i;

	tmp = mini->cmd;
	i = 1;
	while (tmp)
	{
		if (tmp->type != TEXT && tmp->type != T_FILE && tmp->type != D_Q && \
				tmp->type != S_Q)
		{
			if (i == 1)
				mini->ast = new_node(tmp->type, i, 0);
			else
				add_node_to_ast(mini, new_node(tmp->type, i, 0));
			i++;
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	mini->ast->n_tk = i - 1;
	return (0);
}
