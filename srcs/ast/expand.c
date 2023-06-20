/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:08:16 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/13 22:19:27 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	free_split(char **sp)
{
	int	i;

	i = 0;
	while (sp[i] != 0)
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}

void	expand_var_aux(char **exp, char **aux, char *sp, t_mini *mini)
{
	(*aux) = get_substr(sp, mini);
	if ((*aux))
	{
		(*exp) = ft_strjoin_2((*exp), (*aux));
		free((*aux));
	}
}

void	free_exp(char ***sp, char **exp, char **s)
{
	free(*s);
	(*s) = (*exp);
	free_split((*sp));
}

void	expand_var(char **s, t_mini *mini, int i, char *exp)
{
	char	**sp;
	char	*aux;

	if (!ft_count_dollar((*s)))
		return ;
	sp = ft_split((*s), '$');
	while (sp[++i] != 0)
	{
		if (!exp)
		{
			if ((*s)[0] != '$')
				aux = ft_strdup(sp[i]);
			else
				aux = get_substr(sp[i], mini);
			if (aux)
			{
				exp = ft_strdup(aux);
				free(aux);
			}
		}
		else
			expand_var_aux(&exp, &aux, sp[i], mini);
	}
	free_exp(&sp, &exp, s);
}

void	ft_expand(t_mini *mini)
{
	t_token	*t;
	int		f_ue;
	int		i;

	t = mini->cmd;
	f_ue = 0;
	i = 1;
	while (t)
	{
		if ((ft_strncmp(t->token, "export", ft_strlen("export") == 0) || \
				ft_strncmp(t->token, "unset", ft_strlen("unset") == 0)) && \
				i == 1)
			f_ue = 1;
		else if (ft_check_dollar(t->token) && (t->type == TEXT || \
					t->type == D_Q) && ft_strlen(t->token) > 1 && !f_ue)
			expand_var(&t->token, mini, -1, NULL);
		t = t->next;
	}
}
