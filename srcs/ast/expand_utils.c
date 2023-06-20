/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:17:24 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/13 22:18:53 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_check_dollar(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '$')
			j++;
		i++;
	}
	return (j);
}

int	ft_count_dollar(char *str)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '$')
			n++;
	}
	return (n);
}

char	*get_substr(char *str, t_mini *mini)
{
	char	*var;

	if (str[0] == '?')
	{
		var = ft_itoa(g_status);
		return (var);
	}
	var = ft_strdup(get_env(str, mini->env));
	if (!var)
		var = ft_calloc(1, sizeof(char));
	return (var);
}
