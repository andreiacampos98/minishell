/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fill_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 09:12:07 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/12 22:50:00 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_fds_aux(t_ast **a)
{
	t_ast	*aux;

	aux = (*a)->prev;
	while (aux && is_ftype(aux->type))
	{
		if (aux->type == OUT)
		{
			(*a)->left->fdout = open(aux->left->cmd->token, \
					O_CREAT | O_TRUNC | O_RDWR, 0000666);
		}
		else if (aux->type == DOUBLE_OUT)
			(*a)->left->fdout = open(aux->left->cmd->token, \
					O_APPEND | O_CREAT | O_RDWR, 0000666);
		else if (aux->type == IN)
			(*a)->left->fdin = open(aux->left->cmd->token, O_RDONLY);
		else
			(*a)->left->fdin = open(".here_doc", O_CREAT | \
					O_WRONLY | O_TRUNC, 0000644);
		if (aux->prev == NULL)
			break ;
		aux = aux->prev;
	}
	(*a) = aux;
}

void	fill_fds_aux2(t_ast **a)
{
	t_ast	*aux;

	aux = (*a);
	while (aux && is_ftype(aux->type))
	{
		if (aux->type == OUT)
		{
			(*a)->right->fdout = open(aux->left->cmd->token, \
					O_CREAT | O_TRUNC | O_RDWR, 0000666);
		}
		else if (aux->type == DOUBLE_OUT)
			(*a)->right->fdout = open(aux->left->cmd->token, \
					O_APPEND | O_CREAT | O_RDWR, 0000666);
		else if (aux->type == IN)
			(*a)->right->fdin = open(aux->left->cmd->token, O_RDONLY);
		else
			(*a)->right->fdin = open(".here_doc", O_CREAT | \
					O_WRONLY | O_TRUNC, 0000644);
		if (aux->prev == NULL || aux->prev->type == PIPE)
			break ;
		aux = aux->prev;
	}
	(*a) = aux;
}

void	fill_fds(t_ast *ast, int n_tk)
{
	t_ast	*a;

	a = ast;
	while (a->i <= n_tk)
	{
		if (a->type == PIPE && a->prev)
			fill_fds_aux(&a);
		else if (a->i == 1 && is_ftype(a->type))
		{
			fill_fds_aux2(&a);
			if (a->i == 1)
				a = a->prev;
		}
		else
		{
			if (a->prev == NULL)
				break ;
			a = a->prev;
		}
	}
}

int	count_red(t_token *tk)
{
	t_token	*t;
	int		i;

	t = tk;
	i = 0;
	while (t)
	{
		if (is_ftype(t->type))
			i++;
		t = t->next;
	}
	return (i);
}
