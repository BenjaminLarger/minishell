/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_env_var_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:11 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 16:02:19 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data_replace_env_var(t_replace_ev_data *rep, int *i)
{
	rep->exp_idx = 0;
	rep->ev_start = 0;
	rep->n_sgl_quotes = 0;
	rep->n_dbl_quotes = 0;
	rep->first_quote = 0;
	*i = 0;
}

static int	expand_env_var(char const *input, int input_len,
	t_replace_ev_data *rep, t_minishell *data)
{
	int	*i;

	i = &rep->i;
	if (is_valid_ev_dollar_sign(input[*i], &rep->n_sgl_quotes,
			&rep->n_dbl_quotes, &rep->first_quote)
		&& (*i + 1) < input_len
		&& input[*i + 1] && is_valid_ev_character(input[*i + 1]))
	{
		rep->ev_start = ++(*i);
		while (*i < input_len && is_valid_ev_character(input[*i]))
			(*i)++;
		rep->temp_ev_key = ft_substr(input, rep->ev_start, *i - rep->ev_start);
		if (!rep->temp_ev_key)
			return (FAILURE);
		rep->temp_ev_value = ft_getenv(data, rep->temp_ev_key);
		if (rep->temp_ev_value != NULL)
		{
			while (*rep->temp_ev_value)
				rep->expanded[rep->exp_idx++] = *rep->temp_ev_value++;
			free(rep->temp_ev_key);
		}
	}
	else
		rep->expanded[rep->exp_idx++] = input[(*i)++];
	return (SUCCESS);
}

char	*replace_env_var_in_substr(char const *input, int input_len,
	t_minishell *data)
{
	t_replace_ev_data	rep;

	if (ft_memchr(input, '$', input_len) == NULL)
		return (ft_substr(input, 0, input_len));
	init_data_replace_env_var(&rep, &rep.i);
	if (get_ev_str_expanded_len(input, input_len, &rep.expanded_len, data)
		== -1)
		return (NULL);
	rep.expanded = (char *)malloc((rep.expanded_len + 1) * sizeof(char));
	if (!rep.expanded)
		return (NULL);
	while (rep.exp_idx < rep.expanded_len && input[rep.i] != '\0')
	{
		if (expand_env_var(input, input_len, &rep, data) == FAILURE)
			return (NULL);
	}
	rep.expanded[rep.exp_idx] = '\0';
	return (rep.expanded);
}
