/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:44:05 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/10 16:27:00 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_tnew(char *str, t_lex_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->next = 0;
	token->token = str;
	token->type = type;
	return (token);
}

t_token	*ft_tnew_2(char *str, t_lex_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->next = 0;
	token->token = str;
	token->type = type;
	free(str);
	return (token);
}

t_token	*ft_tokenlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_tadd_b(t_token **lst, t_token *tnew)
{
	t_token	*aux;

	if (lst)
	{
		if (*lst)
		{
			aux = ft_tokenlast(*lst);
			aux->next = tnew;
			tnew->prev = aux;
			if (is_ftype(aux->type) == 1 && ft_strncmp(tnew->token, "|", 2) && \
					ft_strncmp(tnew->token, "<", 2) && \
					ft_strncmp(tnew->token, ">", 2) && \
					ft_strncmp(tnew->token, ">>", 3) && \
					ft_strncmp(tnew->token, "<<", 3))
				tnew->type = T_FILE;
		}
		else
			*lst = tnew;
	}
}

int	ft_sl(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != c && str[i])
		i++;
	return (i);
}
