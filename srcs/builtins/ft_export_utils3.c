/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:47:50 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 16:09:09 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export_aux_5(t_mini *mini, t_token *tmp, int *len, int *t)
{
	char	*tmp1;
	char	*tmp2;

	(*len) = ft_sl(tmp->token, '=');
	(*t) = ft_strlen(tmp->token);
	tmp1 = ft_substr(tmp->token, (*len + 1), (*t));
	tmp2 = ft_substr(tmp->token, 0, (*len));
	if (mini->n_exp == 0)
		ft_envadd_b2(&mini->exp, ft_env_new2(tmp1, tmp2, mini), 0);
	else
		ft_envadd_b2(&mini->exp, ft_env_new2(tmp1, tmp2, mini), 1);
	free(tmp1);
	free(tmp2);
	return (1);
}

void	ft_export_aux_2(t_mini *m, t_token *tp, int *l, int *t)
{
	t_token	*c;
	int		f;

	f = 0;
	c = m->full_cmd;
	while (tp)
	{
		while (c)
		{
			if (!ft_strncmp(tp->token, c->token, ft_strlen(tp->token)) \
					&& ft_isequal(c->token) && !check_env(m->env, tp->token) \
					&& !ft_strncmp(tp->token, c->token, ft_strlen(c->token)))
			{
				f = 1;
				(*l) = ft_strlen(tp->token);
				(*t) = ft_strlen(c->token);
				ft_envadd_b(&m->env, ft_env_new(ft_substr(c->token, (*l) + 1, \
								(*t)), tp->token));
			}
			c = c->next;
		}
		if (ft_strncmp(tp->token, "export", ft_strlen(tp->token)) && !f)
			f = ft_export_aux_5(m, tp, l, t);
		tp = tp->next;
	}
}

int	ft_find_red(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '<' && str[i] != '>')
		i++;
	return (i);
}

int	ft_check_env(t_env	*env, t_token *tk, char c)
{
	t_env	*e;
	int		l;
	char	*s;

	e = env;
	l = ft_sl(tk->token, c);
	s = ft_substr(tk->token, 0, l);
	while (e)
	{
		if (!ft_strncmp(e->n, s, ft_strlen(e->n)) && \
				!ft_strncmp(e->n, s, ft_strlen(s)))
		{
			free(s);
			return (0);
		}
		e = e->next;
	}
	free(s);
	return (1);
}

void	ft_export_print(t_env *lst, t_mini *mini, t_env *exp)
{
	while (lst)
	{
		ft_putstr_fd("declare -x ", mini->fdout);
		ft_putstr_fd(lst->n, mini->fdout);
		ft_putstr_fd("=", mini->fdout);
		ft_putstr_fd("\"", mini->fdout);
		ft_putstr_fd(lst->t, mini->fdout);
		ft_putstr_fd("\"\n", mini->fdout);
		lst = lst->next;
	}
	while (exp && mini->n_exp > 0)
	{
		if (!check_env(mini->env, exp->n) && ft_exp_len(exp) > 0 && \
				ft_strncmp(exp->n, "export", ft_strlen(exp->n)))
		{
			ft_putstr_fd("declare -x ", mini->fdout);
			ft_putstr_fd(exp->n, mini->fdout);
			ft_putstr_fd("\n", mini->fdout);
		}
		if (exp->next == NULL)
			break ;
		exp = exp->next;
	}
}
