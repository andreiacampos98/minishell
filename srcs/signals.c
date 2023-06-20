/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 22:31:13 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/09 21:31:17 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

/*Function int rl_on_new_line ()
Tell the update routines that we have moved onto a new (empty) line,
usually after ouputting a newline. */

/*Function void rl_replace_line (const char *text, int clear undo)
Replace the contents of rl_line_buffer with text. The point and mark are pre-
served, if possible. If clear undo is non-zero, the undo list associated with 
the current line is cleared.*/

/*Function int rl_redisplay ()
Change what's displayed on the screen to reflect the current
contents of rl_line_buffer.*/

void	not_finish(int sig_num)
{
	if (sig_num == SIGINT)
	{
		g_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	not_finish_1(int sig_num)
{
	if (sig_num == SIGINT)
	{
		g_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
