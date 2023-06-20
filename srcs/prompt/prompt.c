/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:47:26 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/12 23:53:17 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

/*Function void rl_clear_history (void)
Clear the history list by deleting all of the entries, in the same manner 
as the History library’s clear_history() function.
This differs from clear_history 
because it frees private data Readline saves in the history list.*/

/*readline will read a line from the terminal and return it, using
prompt as a prompt. (If prompt is NULL or the empty string, no
prompt is issued.)
The prompt will be filled by the fill_prompt function.*/
/* Function add_history ()
If the line has any text in it, save it on the history. */

char	*get_pwd_str(void)
{
	char	*str;
	char	cwd[4096];
	char	*path;
	int		i;

	i = -1;
	str = getcwd(cwd, 4096);
	path = ft_calloc(sizeof(char), ft_strlen(cwd) + 1);
	while (cwd[++i])
		path[i] = cwd[i];
	return (path);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*dest;
	size_t	len;

	len = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = ft_calloc(sizeof(char), len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, ft_strlen(s1));
	ft_memcpy(dest + ft_strlen(s1), s2, ft_strlen(s2));
	free(s1);
	return (dest);
}

char	*get_host_str(t_mini *mini)
{
	int		fd;
	char	*aux;
	char	*str;
	char	*str1;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (NULL);
	aux = get_next_line(fd);
	if (!aux)
		return (NULL);
	str = ft_substr(aux, 0, ft_strchr(aux, '.') - aux);
	close(fd);
	free(aux);
	str1 = ft_strdup(get_env("USER", mini->env));
	str1 = ft_strjoin_2(str1, "@");
	str1 = ft_strjoin_2(str1, str);
	str1 = ft_strjoin_2(str1, ":");
	free(str);
	return (str1);
}

char	*get_home_str(void)
{
	char	*str;

	str = ft_strdup(getenv("HOME"));
	if (!str)
		str = ft_strdup("/");
	return (str);
}

char	*create_prompt(t_mini *mini)
{
	char	*pwd_str;
	char	*home_str;
	char	*prompt;
	char	*host_str;

	prompt = NULL;
	host_str = get_host_str(mini);
	pwd_str = get_pwd_str();
	home_str = get_home_str();
	prompt = ft_strjoin_2(prompt, host_str);
	if (ft_strncmp(pwd_str, home_str, ft_strlen(home_str)) == 0)
	{
		prompt = ft_strjoin_2(prompt, "~");
		prompt = ft_strjoin_2(prompt, pwd_str + ft_strlen(home_str));
	}
	else
		prompt = ft_strjoin_2(prompt, pwd_str);
	prompt = ft_strjoin_2(prompt, "$ ");
	free(pwd_str);
	free(home_str);
	free(host_str);
	pwd_str = NULL;
	home_str = NULL;
	host_str = NULL;
	return (prompt);
}
