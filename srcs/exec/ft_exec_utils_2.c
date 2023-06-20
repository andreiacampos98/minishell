/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:40:50 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/08 20:38:33 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_aux(char **path, char ***token, char ***tmp, int f)
{
	if (*path)
		free(*path);
	if (f == 1 && *token)
		free_array(*token, 0);
	if (*tmp)
		free_array(*tmp, 1);
}
