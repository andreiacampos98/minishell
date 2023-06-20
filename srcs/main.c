/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:54:25 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/13 04:02:02 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init_lst_env(&mini, envp, 0);
	while (1)
	{
		signal(SIGINT, not_finish);
		signal(SIGQUIT, SIG_IGN);
		readline_prep(&mini);
		if (mini.line_read == NULL)
			break ;
		if (ft_strlen(mini.line_read) == 0)
		{
			free(mini.prompt);
			continue ;
		}
		if (call_lexer(&mini))
			continue ;
		ft_expand(&mini);
		call_ast(&mini);
		go_minishell(&mini);
		free_cycle(&mini);
	}
}
