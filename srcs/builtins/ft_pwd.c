/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:35:51 by anaraujo          #+#    #+#             */
/*   Updated: 2023/05/27 14:40:34 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_pwd(t_mini *mini)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putstr_fd(buf, mini->fdout);
	ft_putstr_fd("\n", mini->fdout);
	free(buf);
	return (0);
}

/*
char *getcwd(char *buf, size_t size);
The getcwd() function shall place an absolute pathname 
of the current working directory in the array pointed 
to by buf, and return buf. 
The pathname copied to the array shall contain no components
that are symbolic links. 
The size argument is the size in bytes of the character
array pointed to by the buf argument.
If buf is a null pointer, the behavior of getcwd()
is unspecified.*/
