/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:36:11 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/13 19:25:52 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_exp_len(t_env *exp)
{
	t_env	*e;
	int		i;

	i = 0;
	e = exp;
	while (e)
	{
		i++;
		if (e->next == NULL)
			break ;
		e = e->next;
	}
	return (i);
}

void	free_env_2(t_env **t, t_env **tmp)
{
	(*tmp) = (*t)->next;
	free((*t)->t);
	free((*t)->n);
}

void	ft_unset_exp(t_mini *mini, t_token *tk, int l)
{
	t_env	*exp;
	t_env	*tmp;

	if (mini->exp && mini->n_exp)
	{
		exp = mini->exp;
		if (!ft_strncmp(tk->token, exp->n, l) && ft_exp_len(exp) == 1 && \
					!ft_strncmp(tk->token, exp->n, ft_strlen(exp->n)))
		{
			free_env(&exp);
			mini->n_exp -= 1;
			return ;
		}
		else if (!ft_strncmp(tk->token, exp->n, l) && \
					!ft_strncmp(tk->token, exp->n, ft_strlen(exp->n)))
		{
			free_env_2(&exp, &tmp);
			*exp = *tmp;
			free(tmp);
			mini->n_exp -= 1;
		}
		tmp = NULL;
		mini->n_exp -= ft_unset_aux4(tk, exp, tmp, l);
		ft_unset_aux(tk, l, mini);
	}
}

int	check_unset(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '=' || s[0] == '+')
		return (1);
	while (s[++i] != '\0')
	{
		if (s[i] <= '+' || (s[i] > '+' && s[i] < '0') || (s[i] > '9' && \
					s[i] < 'A') || (s[i] > 'Z' && s[i] < '_') || \
				s[i] == '`' || s[i] > 'z')
			return (1);
		else
		{
			if (s[i] >= '0' && s[i] <= '9' && i == 0)
				return (1);
		}
	}
	return (0);
}

int	ft_unset(t_mini *mini, int l)
{
	t_env	*tmp;
	t_env	*curr;
	t_token	*tk;

	tk = mini->cmd->next;
	while (tk)
	{
		if (check_unset(tk->token))
			return (error_handler2(1, "unset", tk->token, 1));
		curr = mini->env;
		l = ft_strlen(tk->token);
		if (!ft_strncmp(tk->token, curr->n, l) && \
				!ft_strncmp(tk->token, curr->n, ft_strlen(curr->n)))
		{
			free_env_2(&curr, &tmp);
			*curr = *tmp;
			free(tmp);
		}
		tmp = NULL;
		ft_unset_aux2(tk, curr, tmp, l);
		ft_unset_aux(tk, l, mini);
		ft_unset_exp(mini, tk, l);
		tk = tk->next;
	}
	return (0);
}
