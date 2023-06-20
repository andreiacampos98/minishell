/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:40:51 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/10 17:22:50 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

/* Function that will look for the path line inside the environment, will
split and test each command path and then return the right one. */
//access() checks whether the calling process can access the file pathname. 
//If pathname is a symbolic link, it is dereferenced. 
char	*find_path(char *cmd, t_env *env)
{
	char	**paths;
	int		i;
	char	*part_path;
	char	*path;

	while (env && env->next && ft_strncmp(env->n, "PATH", 4) != 0)
		env = env->next;
	paths = ft_split(env->t, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_array(paths, 1);
			return (path);
		}
		free(path);
	}
	free_array(paths, 1);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	return (0);
}

int	ft_envsize(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		env = env->next;
		count++;
	}
	return (count);
}

char	**list_to_array(t_env *env)
{
	char	**tmp;
	char	*aux;
	int		i;

	tmp = malloc(sizeof(char *) * (ft_envsize(env) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (env)
	{
		aux = ft_strjoin(env->n, "=");
		tmp[i] = ft_strjoin(aux, env->t);
		i++;
		free(aux);
		env = env->next;
	}
	tmp[i] = NULL;
	return (tmp);
}

int	ft_tokensize(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

char	**token_to_array(t_token *token)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (ft_tokensize(token) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (token)
	{
		tmp[i] = token->token;
		i++;
		token = token->next;
	}
	tmp[i] = NULL;
	return (tmp);
}
