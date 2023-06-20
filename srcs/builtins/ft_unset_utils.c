/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:22:27 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 16:29:01 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset_aux(t_token *tk, int l, t_mini *mini)
{
	t_token	*c;
	t_token	*t;

	c = mini->full_cmd;
	if (!ft_strncmp(tk->token, c->token, l) && \
			!ft_strncmp(tk->token, c->token, ft_strlen(c->token)))
	{
		t = c->next;
		*c = *t;
	}
	t = NULL;
	ft_unset_aux3(tk, c, t, l);
}

void	ft_unset_aux2(t_token *tk, t_env *curr, t_env *tmp, int l)
{
	while (curr->next)
	{
		if (!ft_strncmp(tk->token, curr->next->n, l) && \
				curr->next->next != NULL && !ft_strncmp(tk->token, \
					curr->next->n, ft_strlen(curr->next->n)))
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			free(tmp->n);
			free(tmp->t);
			free(tmp);
		}
		if (!ft_strncmp(tk->token, curr->next->n, l) && \
				curr->next->next == NULL && !ft_strncmp(tk->token, \
					curr->next->n, ft_strlen(curr->next->n)))
		{
			tmp = curr->next;
			curr->next = NULL;
			free(tmp->n);
			free(tmp->t);
			free(tmp);
			break ;
		}
		curr = curr->next;
	}
}

void	ft_unset_aux3(t_token *tk, t_token *c, t_token *t, int l)
{
	while (c->next)
	{
		if (!ft_strncmp(tk->token, c->next->token, l) && \
				c->next->next != NULL && !ft_strncmp(tk->token, \
					c->next->token, ft_strlen(c->next->token)))
		{
			t = c->next;
			c->next = c->next->next;
			free(t->token);
			free(t);
		}
		if (!ft_strncmp(tk->token, c->next->token, l) && \
				c->next->next == NULL && !ft_strncmp(tk->token, \
					c->next->token, ft_strlen(c->next->token)))
		{
			t = c->next;
			c->next = NULL;
			free(t->token);
			free(t);
			break ;
		}
		c = c->next;
	}
}

void	free_env(t_env **t)
{
	free((*t)->n);
	free((*t)->t);
	free((*t));
}

void	ft_unset_aux5(int *i, t_env **curr, t_env **tmp)
{
	(*tmp) = (*curr)->next;
	(*curr)->next = (*curr)->next->next;
	free_env(tmp);
	(*i)++;
}
