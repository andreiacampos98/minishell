/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:28:41 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 16:29:05 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset_aux4(t_token *tk, t_env *curr, t_env *tmp, int l)
{
	int	i;

	i = 0;
	while (curr->next)
	{
		if (!ft_strncmp(tk->token, curr->next->n, l) && \
				curr->next->next != NULL && !ft_strncmp(tk->token, \
					curr->next->n, ft_strlen(curr->next->n)))
			ft_unset_aux5(&i, &curr, &tmp);
		if (!ft_strncmp(tk->token, curr->next->n, l) && \
				curr->next->next == NULL && !ft_strncmp(tk->token, \
					curr->next->n, ft_strlen(curr->next->n)))
		{
			tmp = curr->next;
			curr->next = NULL;
			free_env(&tmp);
			i++;
			break ;
		}
		curr = curr->next;
	}
	return (i);
}
