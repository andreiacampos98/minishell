/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:46:24 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/12 19:31:16 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	init_lst_env(t_mini *mini, char **e, int i)
{
	t_env	*lst_env;
	char	*s1;
	char	*s2;

	lst_env = malloc(sizeof(t_env));
	lst_env->t = ft_substr(e[0], ft_sl(e[0], \
					'=') + 1, ft_strlen(e[0]));
	lst_env->n = ft_substr(e[0], 0, ft_sl(e[0], '='));
	lst_env->next = NULL;
	g_status = 0;
	ft_bzero(mini, sizeof(t_mini));
	mini->env = lst_env;
	mini->i_exec = 1;
	while (e && e[0] && e[++i])
	{
		s1 = ft_substr(e[i], ft_sl(e[i], '=') + 1, ft_strlen(e[i]));
		s2 = ft_substr(e[i], 0, ft_sl(e[i], '='));
		ft_envadd_b(&lst_env, ft_env_new(s1, s2));
		free(s1);
		free(s2);
	}
	return (0);
}

t_env	*ft_env_new(char *str1, char *str2)
{
	t_env	*lst_env;

	lst_env = malloc(sizeof(t_env));
	if (!lst_env)
		return (NULL);
	lst_env->t = ft_strdup(str1);
	lst_env->n = ft_strdup(str2);
	lst_env->next = NULL;
	return (lst_env);
}
