/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokens_assign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:01:44 by demre             #+#    #+#             */
/*   Updated: 2024/03/23 17:55:43 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialise variables used in the index-related data structure.
 */
static void	initialise_index_data(t_index_data *data, int *i)
{
	*i = 0;
	data->j = 0;
	data->start = 0;
	data->n_sgl_quotes = 0;
	data->n_dbl_quotes = 0;
}

/**
 * @brief Store a token extracted from the input string into the tokens array.
 * This function extracts a substring from the input string based on start and 
 * end indices, allocates memory for it, and stores it in the tokens array.
 * @return int SUCCESS if storing the token is successful, FAILURE otherwise.
 */
static int	store_token(char **tokens, char const *str, t_index_data *data,
	int i)
{
	char	*temp_string;

	temp_string
		= replace_env_var_in_substr(&str[data->start], (i - data->start));
	if (!temp_string)
	{
		free_n_string_array(tokens, data->j);
		return (FAILURE);
	}
	if (!ft_strchr(temp_string, '\'') && !ft_strchr(temp_string, '\"'))
		tokens[data->j] = ft_strdup(temp_string);
	else
		tokens[data->j] = remove_quotes_from_str(temp_string);
	if (!tokens[data->j])
	{
		free_n_string_array(tokens, data->j);
		free(temp_string);
		return (FAILURE);
	}
	free(temp_string);
	dprintf(2, "tokens[data->j]: %s\n\n", tokens[data->j]); //
	data->j++;
	return (SUCCESS);
}

static void	set_start_and_increment_index(int *start, int *index, int increment)
{
	*start = *index;
	*index += increment;
}

static int	call_store_tokens(char **tokens, char const *str,
	t_index_data *data, int i)
{
	if (data->start < i)
	{
		if (store_token(tokens, str, data, i) == FAILURE)
			return (FAILURE);
	}
	else if (islinker_outside_quotes(&str[i], data))
	{
		if (is_dbl_linker(&str[i]))
			set_start_and_increment_index(&data->start, &i, 2);
		else
			set_start_and_increment_index(&data->start, &i, 1);
		if (store_token(tokens, str, data, i) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Break down a string into individual tokens based on whitespace and 
 * quotes.
 * @param tokens Pointer to the array of strings where tokens will be storedata.
 * @param str Pointer to the input string to tokenize.
 * @return int SUCCESS if tokenization is successful, FAILURE otherwise.
 */
int	assign_tokens(char **tokens, char const *str)
{
	t_index_data	data;
	int				i;

	initialise_index_data(&data, &i);
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		data.start = i;
		while (str[i]
			&& !isspace_outside_quotes(str[i], &data)
			&& !islinker_outside_quotes(&str[i], &data)
		)
			increase_quote_count_if_outside_quotes(str[i++],
				&data.n_sgl_quotes, &data.n_dbl_quotes);
		if (data.n_sgl_quotes % 2 == 1 || data.n_dbl_quotes % 2 == 1)
			return (FAILURE);
		if (call_store_tokens(tokens, str, &data, i) == FAILURE)
			return (FAILURE);
	}
	tokens[data.j] = NULL;
	return (SUCCESS);
}
