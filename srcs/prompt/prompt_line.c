/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:56:33 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/05 18:32:59 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	readline_prep(t_mini *mini)
{
	mini->prompt = create_prompt(mini);
	mini->line_read = readline(mini->prompt);
	if (mini->line_read == NULL)
		free_everything(mini, 0);
	if (mini->line_read && *mini->line_read)
		add_history(mini->line_read);
}
