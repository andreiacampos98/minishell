/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:36:02 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/13 04:08:11 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_atoi_export_aux(char *str, int i, int a)
{
	if (a)
	{
		if (str[i] < '+' || (str[i] > '+' && str[i] < '0') || (str[i] > '9' && \
					str[i] < 'A') || (str[i] > 'Z' && str[i] < '_') || \
				str[i] == '`' || str[i] > 'z')
			return (1);
		return (0);
	}
	else
	{
		if (str[i] < '!' || str[i] == '#' || str[i] == '"' || \
				(str[i] > '%' && str[i] < '*') || str[i] == '^' || \
				str[i] == '`' || str[i] == '|' || str[i] > '~')
			return (1);
		return (0);
	}
}

int	ft_atoi_export(char *str, t_lex_type type)
{
	int	i;
	int	l;

	i = -1;
	l = 0;
	if ((type == D_Q || type == S_Q) && !ft_strlen(str))
		return (0);
	if (str[0] == '=' || str[0] == '+')
		return (0);
	while (str[++i] != '\0' && str[i] != '=')
	{
		if (ft_atoi_export_aux(str, i, 1))
			return (0);
		else
		{
			if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && \
						str[i] <= 'Z'))
				l = 1;
			else if (str[i] >= '0' && str[i] <= '9' && i == 0)
				return (0);
			else if (str[i] == '+' && str[i + 1] != '=')
				return (0);
		}
	}
	return (1);
}

int	valid_value(char *s, t_lex_type type)
{
	int	i;
	int	f;

	i = -1;
	f = 0;
	if ((type == D_Q || type == S_Q) && !ft_strlen(s))
		return (0);
	if (s)
	{
		while (s[++i] != '\0')
		{
			if (ft_atoi_export_aux(s, i, 0))
				return (0);
			else
			{
				if (s[i] == '>' || s[i] == '<')
					f = 1;
				else if ((s[i] == '/' || s[i] == '\\') && s[i + 1] == '\0')
					return (2);
			}
		}
	}
	if (f == 1)
		return (1);
	return (3);
}

void	ft_export2(t_mini *mini, t_token *tmp, int *len, int *t)
{
	if (ft_atoi_export(tmp->token, tmp->type) && \
			!(tmp->token[0] == '_' && tmp->token[1] == '='))
	{
		if ((valid_value(ft_strrchr(tmp->token, '='), tmp->type) != 0 && \
					valid_value(ft_strrchr(tmp->token, '='), tmp->type) != 2))
		{
			if (ft_isequal(tmp->token) == 1)
				ft_export_aux_1(mini, tmp, len, t);
			else
				ft_export_aux_2(mini, tmp, len, t);
		}
		else
			error_handler2(130, "export", tmp->token, 2);
	}
	else if (!ft_atoi_export(tmp->token, tmp->type))
		error_handler2(1, "export", tmp->token, 1);
}

int	ft_export(t_mini *mini, t_token *tk)
{
	t_token	*tmp;
	int		len;
	int		t;

	tmp = tk;
	if (tmp->next == NULL || check_cardinal_ampers(tmp->next) == 1)
		ft_export_print(mini->env, mini, mini->exp);
	else if (check_cardinal_ampers(tmp->next) == 2)
		ampersand(mini, tmp->next);
	else
	{
		tmp = tmp->next;
		while (tmp)
		{
			ft_export2(mini, tmp, &len, &t);
			tmp = tmp->next;
		}
	}
	return (g_status);
}
