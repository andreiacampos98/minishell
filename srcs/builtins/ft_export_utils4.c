/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:16:39 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 16:09:15 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_atoi_export2(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
	}
	return (0);
}

void	ft_export_aux_1_aux(t_mini *mini, t_token *tmp, int *len, int *t)
{
	char	*str;
	char	*var;
	t_env	*e;
	char	*tmp1;

	e = mini->env;
	(*len) = ft_sl(tmp->token, '+');
	(*t) = ft_strlen(tmp->token);
	str = ft_substr(tmp->token, (*len + 2), (*t));
	var = ft_substr(tmp->token, 0, (*len));
	while (e)
	{
		if (!ft_strncmp(e->n, var, ft_strlen(e->n)) && \
				!ft_strncmp(e->n, var, ft_strlen(var)))
		{
			tmp1 = ft_strjoin(e->t, str);
			free(e->t);
			e->t = tmp1;
		}
		e = e->next;
	}
	free(str);
	free(var);
}

void	ft_export_aux1_aux(char **tmp1, char **tmp2)
{
	free(*tmp1);
	free(*tmp2);
}

int	ft_isequal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_set_new_value_env(t_env	*env, t_token *tk)
{
	t_env	*e;
	int		len;
	int		l;
	char	*s;

	e = env;
	len = ft_sl(tk->token, '=');
	l = ft_strlen(tk->token);
	s = ft_substr(tk->token, 0, len);
	while (e)
	{
		if (!ft_strncmp(e->n, s, ft_strlen(e->n)) && \
				!ft_strncmp(e->n, s, ft_strlen(s)))
			e->t = ft_substr(tk->token, len + 1, l);
		e = e->next;
	}
	free(s);
}
