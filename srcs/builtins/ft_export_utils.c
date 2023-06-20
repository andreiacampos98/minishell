/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:46:03 by csilva-f          #+#    #+#             */
/*   Updated: 2023/05/29 20:11:59 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cardinal_ampers(t_token *lst)
{
	if (lst->token[0] == '#')
		return (1);
	else if (lst->token[0] == '&')
		return (2);
	return (0);
}

void	ft_set_new_value_env2(t_env	*env, t_token *token)
{
	t_env	*e;
	int		len;
	int		l;
	char	*s;

	e = env;
	s = ft_substr(token->token, 0, ft_find_red(token->token));
	len = ft_sl(s, '=');
	l = ft_strlen(s);
	while (e)
	{
		if (!ft_strncmp(e->n, s, ft_strlen(e->n)) && \
				!ft_strncmp(e->n, s, ft_strlen(s)))
			e->t = ft_substr(s, len + 1, l);
		e = e->next;
	}
}

int	ft_check_env2(t_env	*env, t_token *token)
{
	t_env	*e;
	char	*s;

	e = env;
	s = ft_substr(token->token, 0, ft_find_red(token->token));
	while (e)
	{
		if (!ft_strncmp(e->n, s, ft_strlen(e->n)) && \
				!ft_strncmp(e->n, s, ft_strlen(s)))
			return (0);
		e = e->next;
	}
	return (1);
}

void	ft_export_aux_3(t_mini *mini, t_token *tmp, int *len, int *t)
{
	char	*s;

	s = ft_substr(tmp->token, 0, ft_find_red(tmp->token));
	if (ft_check_env2(mini->env, tmp))
	{
		(*len) = ft_sl(s, '=');
		(*t) = ft_strlen(s);
		ft_envadd_b(&mini->env, ft_env_new(ft_substr(s, \
						(*len + 1), (*t)), ft_substr(s, 0, (*len))));
	}
	else
		ft_set_new_value_env2(mini->env, tmp);
}

void	ft_export_aux_4(t_mini *mini, t_token *tmp, int *len, int *t)
{
	t_token	*cur_1;
	char	*s;

	cur_1 = mini->full_cmd;
	while (tmp)
	{
		s = ft_substr(tmp->token, 0, ft_find_red(tmp->token));
		while (cur_1)
		{
			if (!ft_strncmp(s, cur_1->token, ft_strlen(s)) && \
					!ft_strncmp(s, cur_1->token, ft_strlen(cur_1->token)) \
					&& ft_isequal(cur_1->token))
			{
				(*len) = ft_strlen(s);
				(*t) = ft_strlen(cur_1->token);
				ft_envadd_b(&mini->env, ft_env_new(\
							ft_substr(cur_1->token, \
								(*len) + 1, (*t)), s));
			}
			cur_1 = cur_1->next;
		}
		tmp = tmp->next;
		free(s);
	}
}
