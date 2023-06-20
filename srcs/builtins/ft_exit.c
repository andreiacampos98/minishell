/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:36:28 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/11 20:17:29 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	ft_hasdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-')
			i++;
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_mini *m, t_token *t)
{
	if (t->next != NULL && t->next->token \
		&& ft_hasdigit(t->next->token) == 1)
	{
		if (t->next->next != NULL)
		{
			ft_tokenclear(&m->cmd);
			ft_printf("exit: too many arguments\n");
			return (1);
		}
		else
			g_status = ft_atoi(t->next->token);
	}
	else if (t->next != NULL && t->next->token \
		&& ft_hasdigit(t->next->token) == 0)
	{
		ft_printf("exit: numeric argument required\n");
		g_status = 2;
	}
	free_everything(m, 0);
	exit(g_status);
}
