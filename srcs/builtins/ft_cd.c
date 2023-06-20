/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:35:35 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/11 18:59:09 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*The chdir command is a system function 
 * (system call) which is used to change 
the current working directory. On some systems,
this command is used as an alias 
for the shell command cd. chdir changes the
current working directory of the calling 
process to the directory specified in path.*/

void	mod_env(char *str, char *str1, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->n, str, ft_strlen(str)) == 0)
		{
			free(env->t);
			env->t = ft_strdup(str1);
			break ;
		}
		env = env->next;
	}
}

void	go_to_home(t_env *env)
{
	char	*old;
	char	*env_path;

	old = get_env("PWD", env);
	env_path = get_env("HOME", env);
	mod_env("OLDPWD", old, env);
	mod_env("PWD", env_path, env);
	chdir(env_path);
}

int	ft_cd(t_token *t, t_env *env)
{
	char	*old;
	char	*pwd;

	old = get_env("PWD", env);
	if (t->next == NULL || t->next->token[0] == '~')
	{
		go_to_home(env);
		return (0);
	}
	else
	{
		mod_env("OLDPWD", old, env);
		if (chdir(t->next->token) != 0)
			return (error_handler2(1, "cd", t->next->token, 0));
		pwd = getcwd(NULL, 0);
		mod_env("PWD", pwd, env);
		free(pwd);
		return (0);
	}
}
