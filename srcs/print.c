/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:09:38 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/12 21:52:22 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstprint(t_token *lst)
{
	char	c;
	char	c_ant;
	t_token	*tk;

	tk = lst;
	c_ant = ' ';
	while (tk)
	{
		c = ft_type(tk->type);
		ft_printf("token: %s ; type: %c\n", tk->token, c);
		if (tk->next == NULL)
			break ;
		tk = tk->next;
		c_ant = c;
	}
}

void	astprint_aux(t_ast *ta)
{
	ft_printf("RIGHT  type: %c ; i: %d ; cmd: ", \
			ft_type(ta->right->type), ta->right->i);
	ft_lstprint(ta->right->cmd);
	ft_printf("fd: %d\n", ta->right->fdout);
	ft_printf("prev i folha: %d\n\n", ta->right->prev->i);
}

void	astprint_aux2(t_ast *ta)
{
	ft_printf("LEFT  type: %c ; i: %d ; cmd: ", \
			ft_type(ta->left->type), ta->left->i);
	ft_lstprint(ta->left->cmd);
	ft_printf("fd: %d\n", ta->left->fdout);
	ft_printf("prev i folha: %d\n\n", ta->right->prev->i);
}

void	ft_astprint(t_ast *ast, int n_tk)
{
	int		i;
	t_ast	*ta;
	char	c;

	i = 1;
	ft_printf("n = %d\n", n_tk);
	ft_printf("------------------------AST-----------------------\n");
	while (i <= n_tk)
	{
		ta = ast;
		while (ta->i > i)
			ta = ta->right;
		c = ft_type(ta->type);
		ft_printf("NODE: %d - type: %c\n", ta->i, c);
		if (ta->prev)
			ft_printf("prev i: %d\n", ta->prev->i);
		if (ta->right != NULL && i == 1)
			astprint_aux(ta);
		if (ta->left != NULL)
			astprint_aux2(ta);
		i++;
	}
	ft_printf("--------------------------------------------------\n");
}

void	ft_envprint(t_env *env)
{
	t_env	*e;

	e = env;
	while (e)
	{
		ft_printf("et: %s        |  en: %s\n", e->t, e->n);
		e = e->next;
	}
}
