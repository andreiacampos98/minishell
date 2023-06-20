/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:35:25 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/11 10:25:13 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	ft_without_newline(t_token **t, int *i, int *newline, int *f)
{
	while ((*t)->token[++(*i)] == 'n')
		(*newline) = 0;
	if ((*t)->token[(*i)] != '\0')
	{
		(*newline) = 1;
		(*t) = (*t)->prev;
		(*f) = 1;
	}
}

int	ft_echo(t_token *t, t_mini *mini)
{
	int	newline;
	int	i;
	int	f;

	newline = 1;
	t = t->next;
	f = 0;
	while (t && t->token)
	{
		i = 0;
		if (t->token[0] == '-' && !f)
			ft_without_newline(&t, &i, &newline, &f);
		else
		{
			ft_putstr_fd(t->token, mini->fdout);
			if (t->next != NULL)
				ft_putstr_fd(" ", mini->fdout);
		}
		if (t->next == NULL)
			break ;
		t = t->next;
	}
	if (newline == 1)
		ft_putstr_fd("\n", mini->fdout);
	return (0);
}
