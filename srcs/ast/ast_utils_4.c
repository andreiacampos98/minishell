/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:58:30 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 19:37:23 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_type(t_lex_type a_type, t_lex_type type)
{
	if (a_type == type)
		return (1);
	return (0);
}

int	ft_n_pipes(t_token *cmd)
{
	t_token	*aux;
	int		n;

	aux = cmd;
	n = 0;
	while (aux)
	{
		if (aux->type == PIPE)
			n++;
		if (aux->next == NULL)
			break ;
		aux = aux->next;
	}
	return (n);
}

int	is_q_text(t_lex_type type)
{
	if (type == D_Q || type == S_Q || type == TEXT || type == T_FILE)
		return (1);
	return (0);
}
