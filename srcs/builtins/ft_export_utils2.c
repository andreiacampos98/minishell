/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:45:56 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 16:12:47 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ampersand(t_mini *mini, t_token *lst)
{
	t_token	*tk;

	tk = lst;
	ft_export_print(mini->env, mini, mini->exp);
	if (tk->next != NULL || ft_strlen(tk->token) > 1)
	{
		if (ft_strlen(tk->token) > 1)
			error_handler3(127, &tk->token[1]);
		else
			error_handler3(127, tk->next->token);
	}
}

void	ft_env_new2_aux(t_env **e, char *str1, char *str2)
{
	(*e) = malloc(sizeof(t_env));
	(*e)->t = ft_strdup(str1);
	(*e)->n = ft_strdup(str2);
	(*e)->next = NULL;
}

t_env	*ft_env_new2(char *str1, char *str2, t_mini *mini)
{
	t_env	*e;
	t_env	*en;
	t_env	*ex;

	en = mini->env;
	ex = mini->exp;
	while (en)
	{
		if (!ft_strncmp(str2, en->n, ft_strlen(str2)) && \
				!ft_strncmp(str2, en->n, ft_strlen(en->n)))
			return (NULL);
		en = en->next;
	}
	while (ex && mini->n_exp)
	{
		if (!ft_strncmp(str2, ex->n, ft_strlen(str2)) && \
				!ft_strncmp(str2, ex->n, ft_strlen(ex->n)))
			return (NULL);
		ex = ex->next;
	}
	mini->n_exp += 1;
	ft_env_new2_aux(&e, str1, str2);
	return (e);
}

int	check_env(t_env *env, char *tk)
{
	t_env	*e;

	e = env;
	while (e)
	{
		if (!ft_strncmp(tk, e->n, ft_strlen(tk)) && \
				!ft_strncmp(tk, e->n, ft_strlen(e->n)))
			return (1);
		e = e->next;
	}
	return (0);
}

void	ft_envadd_b2(t_env **lst, t_env *enew, int n)
{
	t_env	*aux;

	if (lst)
	{
		if (*lst && n)
		{
			aux = ft_envlast(*lst);
			aux->next = enew;
		}
		else
			*lst = enew;
	}
}
