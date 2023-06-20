/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:04:02 by anaraujo          #+#    #+#             */
/*   Updated: 2023/04/18 22:30:56 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *lnew)
{
	t_list	*aux;

	if (lst)
	{
		if (*lst)
		{
			aux = ft_lstlast(*lst);
			aux->next = lnew;
		}
		else
			*lst = lnew;
	}
}
