/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 04:09:00 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/13 04:09:13 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export_aux_1(t_mini *m, t_token *tmp, int *len, int *t)
{
	char	*tmp1;
	char	*tmp2;

	if (ft_check_env(m->env, tmp, '=') == 1 && !ft_atoi_export2(tmp->token))
	{
		(*len) = ft_sl(tmp->token, '=');
		(*t) = ft_strlen(tmp->token);
		tmp1 = ft_substr(tmp->token, (*len + 1), (*t));
		tmp2 = ft_substr(tmp->token, 0, (*len));
		ft_envadd_b(&m->env, ft_env_new(tmp1, tmp2));
		ft_export_aux1_aux(&tmp1, &tmp2);
	}
	else if (ft_check_env(m->env, tmp, '+') == 1 && ft_atoi_export2(tmp->token))
	{
		(*len) = ft_sl(tmp->token, '+');
		(*t) = ft_strlen(tmp->token);
		tmp1 = ft_substr(tmp->token, (*len + 2), (*t));
		tmp2 = ft_substr(tmp->token, 0, (*len));
		ft_envadd_b(&m->env, ft_env_new(tmp1, tmp2));
		ft_export_aux1_aux(&tmp1, &tmp2);
	}
	else if (!ft_check_env(m->env, tmp, '+') && ft_atoi_export2(tmp->token))
		ft_export_aux_1_aux(m, tmp, len, t);
	else
		ft_set_new_value_env(m->env, tmp);
}
