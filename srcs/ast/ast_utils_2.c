/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:04:22 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/10 17:37:09 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_tokendup(t_token *tk)
{
	t_token	*new;
	t_token	*aux;

	new = NULL;
	if (tk)
	{
		aux = tk;
		while (aux)
		{
			if (!new)
				new = ft_tnew(ft_strdup(aux->token), aux->type);
			else
				ft_tadd_b(&new, ft_tnew(ft_strdup(aux->token), aux->type));
			aux = aux->next;
		}
		return (new);
	}
	return (NULL);
}

void	build_ast_aux5(t_aux *a, t_mini *mini)
{
	a->p = 0;
	a->p2 = 0;
	a->cmd = mini->cmd;
	a->tk = NULL;
}

void	fill_ast_file_aux(t_mini *mini, t_token *tmp)
{
	t_ast	*tmpa;
	t_token	*tk;
	int		i;

	i = 1;
	tmpa = mini->ast;
	while (tmpa->i > i && tmpa)
		tmpa = tmpa->right;
	while (!is_ftype(tmpa->type) || (is_ftype(tmpa->type) \
				&& tmpa->left != NULL))
	{
		i++;
		tmpa = mini->ast;
		while (tmpa->i > i)
			tmpa = tmpa->right;
	}
	tk = ft_tnew(ft_strdup(tmp->next->token), T_FILE);
	tmpa->left = new_node(tk->type, i, 0);
	tmpa->left->cmd = ft_tnew(ft_strdup(tk->token), tk->type);
	tmpa->left->prev = tmpa;
	ft_tokenclear(&tk);
	free(tk);
}

int	fill_ast_file(t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->cmd;
	if (build_ast_base(mini))
		return (1);
	while (tmp)
	{
		if (is_ftype(tmp->type) == 1)
		{
			fill_ast_file_aux(mini, tmp);
			if (tmp->next->next == NULL)
				break ;
			tmp = tmp->next;
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (0);
}

void	build_ast_aux(t_mini *mini, t_aux *a)
{
	t_ast	*ast;

	ast = mini->ast;
	while (ast->i > a->i)
		ast = ast->right;
	if (ast->right == NULL)
	{
		ast->right = new_node(a->tk->type, a->i, 0);
		ast->right->cmd = ft_tokendup(a->tk);
		ast->right->prev = ast;
	}
	else
	{
		while (ast->left != NULL)
		{
			a->i++;
			ast = mini->ast;
			while (ast->i > a->i)
				ast = ast->right;
		}
		ast->left = new_node(a->tk->type, a->i, 0);
		ast->left->cmd = ft_tokendup(a->tk);
		ast->left->prev = ast;
	}
	ft_tokenclear(&a->tk);
}
