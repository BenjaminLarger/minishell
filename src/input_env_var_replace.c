/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_env_var_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:11 by demre             #+#    #+#             */
/*   Updated: 2024/03/23 18:12:10 by demre            ###   ########.fr       */
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
	t_replace_ev_data *rep, int *i)
{
	if (is_valid_ev_dollar_sign(input[*i], &rep->n_sgl_quotes,
			&rep->n_dbl_quotes, &rep->first_quote)
		&& (*i + 1) < input_len
		&& input[*i + 1] && is_valid_ev_character(input[*i + 1]))
	{
		rep->ev_start = ++(*i);
		while (*i < input_len && is_valid_ev_character(input[*i]))
			(*i)++;
		rep->temp_ev_name = ft_substr(input, rep->ev_start, *i - rep->ev_start);
		if (!rep->temp_ev_name)
			return (FAILURE);
		rep->temp_ev_value = getenv(rep->temp_ev_name);
		if (rep->temp_ev_value != NULL)
		{
			dprintf(2, "temp_ev_name: %s, getenv(temp_ev_name): %s, *i: %d\n", rep->temp_ev_name, getenv(rep->temp_ev_name), *i); //
			while (*rep->temp_ev_value)
				rep->expanded[rep->exp_idx++] = *rep->temp_ev_value++;
			free(rep->temp_ev_name);
		}
	}
	else
		rep->expanded[rep->exp_idx++] = input[(*i)++];
	return (SUCCESS);
}

char	*replace_env_var_in_substr(char const *input, int input_len)
{
	t_replace_ev_data	rep;
	int					i;

	if (ft_memchr(input, '$', input_len) == NULL)
		return (ft_substr(input, 0, input_len));
	init_data_replace_env_var(&rep, &i);
	if (get_ev_str_expanded_len(input, input_len, &rep.expanded_len) == -1)
		return (NULL);
	rep.expanded = (char *)malloc((rep.expanded_len + 1) * sizeof(char));
	if (!rep.expanded)
		return (NULL);
	while (rep.exp_idx < rep.expanded_len && input[i] != '\0')
	{
		if (expand_env_var(input, input_len, &rep, &i) == FAILURE)
			return (NULL);
	}
	rep.expanded[rep.exp_idx] = '\0';
	dprintf(2, "expanded: %s\n", rep.expanded); //
	return (rep.expanded);
}
