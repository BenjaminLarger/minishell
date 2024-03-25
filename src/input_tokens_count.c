/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokens_count.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:01:55 by demre             #+#    #+#             */
/*   Updated: 2024/03/25 14:10:11 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialise variables used in the token-related data structure.
 * @param t Pointer to the token data structure to be initialised.
 */
static void	initialise_token_data(t_token_data *data, int *i)
{
	*i = 0;
	data->n_tokens = 0;
	data->is_inside_token = TRUE;
	data->n_sgl_quotes = 0;
	data->n_dbl_quotes = 0;
}

static void	handle_two_character_linker(t_token_data *data, int *i)
{
	data->is_inside_token = FALSE;
	data->n_tokens++;
	(*i)++;
}

static void	handle_one_character_linker(t_token_data *data)
{
	data->is_inside_token = FALSE;
	data->n_tokens++;
}

static void	handle_new_token(t_token_data *data)
{
	data->is_inside_token = TRUE;
	data->n_tokens++;
}

int	count_tokens(char const *str)
{
	t_token_data	data;
	int				i;

	initialise_token_data(&data, &i);
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		increase_quote_count_if_outside_quotes(str[i], &data.n_sgl_quotes,
			&data.n_dbl_quotes);
		if (is_dbl_linker(&str[i]) && is_outside_quotes(&data))
			handle_two_character_linker(&data, &i);
		else if (is_sgl_linker(&str[i]) && is_outside_quotes(&data))
			handle_one_character_linker(&data);
		else if (ft_isspace(str[i]) && is_outside_quotes(&data))
			data.is_inside_token = FALSE;
		else if (i == 0 && !ft_isspace(str[i]))
			data.n_tokens++;
		else if (data.is_inside_token == FALSE)
			handle_new_token(&data);
		i++;
	}
	if (data.n_sgl_quotes % 2 == 1 || data.n_dbl_quotes % 2 == 1)
		data.n_tokens = 0;
	return (data.n_tokens);
}
