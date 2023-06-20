/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:36:19 by anaraujo          #+#    #+#             */
/*   Updated: 2023/05/29 19:39:42 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_env(t_env *lst, t_mini *mini)
{
	while (lst)
	{
		ft_putstr_fd(lst->n, mini->fdout);
		ft_putstr_fd("=", mini->fdout);
		ft_putstr_fd(lst->t, mini->fdout);
		ft_putstr_fd("\n", mini->fdout);
		lst = lst->next;
	}
	return (0);
}

char	*get_env(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->n, str, ft_strlen(str)) == 0)
			return (env->t);
		env = env->next;
	}
	return (NULL);
}

t_env	*ft_envlast(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	ft_envadd_b(t_env **lst, t_env *enew)
{
	t_env	*aux;

	if (lst)
	{
		if (*lst)
		{
			aux = ft_envlast(*lst);
			aux->next = enew;
		}
		else
			*lst = enew;
	}
}

void	set_env(t_env *envp, char *name, char *text)
{
	t_env	*env;

	env = ft_envlast(envp);
	ft_envadd_b(&env, ft_env_new(name, text));
}
