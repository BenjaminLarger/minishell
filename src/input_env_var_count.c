/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_env_var_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:11 by demre             #+#    #+#             */
/*   Updated: 2024/03/23 16:34:51 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data_calculate_expanded_len(t_expanded_data *exp, int *i)
{
	*i = 0;
	exp->expanded_len = 0;
	exp->ev_start = 0;
	exp->n_sgl_quotes = 0;
	exp->n_dbl_quotes = 0;
	exp->first_quote = no_quote;
}

static void	increment_index_and_length(int *i, int *expanded_len)
{
	*i += 1;
	*expanded_len += 1;
}

static int	calculate_expanded_len(char const *input, int input_len)
{
	t_expanded_data	exp;
	int				i;

	init_data_calculate_expanded_len(&exp, &i);
	while (i < input_len && input[i])
	{
		if (is_valid_ev_dollar_sign(input[i], &exp.n_sgl_quotes,
				&exp.n_dbl_quotes, &exp.first_quote) && (i + 1) < input_len
			&& input[i + 1] && is_valid_ev_character(input[i + 1]))
		{
			exp.ev_start = ++i;
			while (i < input_len && is_valid_ev_character(input[i]))
				i++;
			exp.temp_ev_name
				= ft_substr(input, exp.ev_start, i - exp.ev_start);
			if (!exp.temp_ev_name)
				return (-1);
			if (getenv(exp.temp_ev_name))
				exp.expanded_len += ft_strlen(getenv(exp.temp_ev_name));
			free(exp.temp_ev_name);
		}
		else
			increment_index_and_length(&i, &exp.expanded_len);
	}
	dprintf(2, "returning exp_len: %d, i: %d\n\n", exp.expanded_len, i);
	return (exp.expanded_len);
}

int	get_ev_str_expanded_len(char const *input, int input_len,
	int *expanded_len)
{
	if (!input || input[0] == '\0')
		*expanded_len = 0;
	else
		*expanded_len = calculate_expanded_len(input, input_len);
	return (*expanded_len);
}
