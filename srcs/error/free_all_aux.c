/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:25:56 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 20:08:54 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_tokenclear(t_token **lst)
{
	t_token	*aux;

	if (!(*lst) || !lst)
		return ;
	while (*lst && lst)
	{
		aux = (*lst)->next;
		free((*lst)->token);
		free(*lst);
		*lst = aux;
	}
}

void	ft_envclear(t_env **env)
{
	t_env	*aux;

	if (!(*env))
		return ;
	while (*env)
	{
		aux = (*env)->next;
		free((*env)->n);
		free((*env)->t);
		free(*env);
		*env = aux;
	}
}

void	free_array(char **array, int lst)
{
	int	i;

	i = 0;
	while (array && array[i] && lst)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cycle(t_mini *mini)
{
	if (mini->cmd != NULL)
		ft_tokenclear(&mini->cmd);
	if (mini->ast != NULL && mini->ast_active)
		ft_astclear(&mini->ast, mini);
	free(mini->line_read);
	free(mini->prompt);
}

void	free_everything(t_mini *mini, int i)
{
	ft_envclear(&mini->env);
	if (mini->n_exp > 0)
		ft_envclear(&mini->exp);
	if (mini->ast && mini->ast_active)
		ft_astclear(&mini->ast, mini);
	ft_tokenclear(&mini->cmd);
	ft_tokenclear(&mini->full_cmd);
	free(mini->line_read);
	free(mini->prompt);
	if (mini->pipes)
	{
		free(mini->pipes);
		mini->pipes = NULL;
	}
	rl_clear_history();
	if (i == 0)
		printf("exit\n");
}

// || !env)
// && env)
