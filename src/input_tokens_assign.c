/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokens_assign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:01:44 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 16:03:16 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialise variables used in the index-related data structure.
 */
static void	initialise_index_data(t_index_data *ind, int *i)
{
	*i = 0;
	ind->j = 0;
	ind->start = 0;
	ind->n_sgl_quotes = 0;
	ind->n_dbl_quotes = 0;
}

/**
 * @brief Store a token extracted from the input string into the tokens array.
 * This function extracts a substring from the input string based on start and 
 * end indices, allocates memory for it, and stores it in the tokens array.
 * @return int SUCCESS if storing the token is successful, FAILURE otherwise.
 */
static int	store_token(t_minishell *data, char const *str, t_index_data *ind,
	int i)
{
	char	*temp_string;

	temp_string
		= replace_env_var_in_substr(&str[ind->start], (i - ind->start), data);
	if (!temp_string)
	{
		free_n_string_array(data->args, ind->j);
		return (FAILURE);
	}
	if (!ft_strchr(temp_string, '\'') && !ft_strchr(temp_string, '\"'))
		data->args[ind->j] = ft_strdup(temp_string);
	else
		data->args[ind->j] = remove_quotes_from_str(temp_string);
	if (!data->args[ind->j])
	{
		free_n_string_array(data->args, ind->j);
		free(temp_string);
		return (FAILURE);
	}
	free(temp_string);
	ind->j++;
	return (SUCCESS);
}

static void	set_start_and_increment_index(int *start, int *i, int increment)
{
	*start = *i;
	*i += increment;
}

static int	call_store_tokens(t_minishell *data, char const *str,
	t_index_data *ind, int *i)
{
	if (ind->start < *i)
	{
		if (store_token(data, str, ind, *i) == FAILURE)
			return (FAILURE);
	}
	else if (islinker_outside_quotes(&str[*i], ind))
	{
		if (is_dbl_linker(&str[*i]))
			set_start_and_increment_index(&ind->start, i, 2);
		else
			set_start_and_increment_index(&ind->start, i, 1);
		if (store_token(data, str, ind, *i) == FAILURE)
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
int	assign_tokens(t_minishell *data, char const *str)
{
	t_index_data	ind;
	int				i;

	initialise_index_data(&ind, &i);
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		ind.start = i;
		while (str[i]
			&& !isspace_outside_quotes(str[i], &ind)
			&& !islinker_outside_quotes(&str[i], &ind)
		)
			increase_quote_count_if_outside_quotes(str[i++],
				&ind.n_sgl_quotes, &ind.n_dbl_quotes);
		if (call_store_tokens(data, str, &ind, &i) == FAILURE)
			return (FAILURE);
	}
	data->args[ind.j] = NULL;
	return (SUCCESS);
}
