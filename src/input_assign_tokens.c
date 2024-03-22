/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_assign_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:01:44 by demre             #+#    #+#             */
/*   Updated: 2024/03/22 19:03:30 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialise variables used in the index-related data structure.
 */
static void	initialise_index_data(t_index_data *d)
{
	d->i = 0;
	d->j = 0;
	d->start = 0;
	d->n_sgl_quotes = 0;
	d->n_dbl_quotes = 0;
}

/**
 * @brief Store a token extracted from the input string into the tokens array.
 * This function extracts a substring from the input string based on start and 
 * end indices, allocates memory for it, and stores it in the tokens array.
 * @return int SUCCESS if storing the token is successful, FAILURE otherwise.
 */
static int	store_token(char **tokens, char const *str, t_index_data *d)
{
	char	*temp_string;

	temp_string = replace_env_var_in_substr(&str[d->start], (d->i - d->start));
	if (!temp_string)
	{
		free_n_string_array(tokens, d->j);
		return (FAILURE);
	}
//	dprintf(2, "temp_string: %s\n", temp_string);

	if (!ft_strchr(temp_string, '\'') && !ft_strchr(temp_string, '\"'))
		tokens[d->j] = ft_strdup(temp_string);
	else
		tokens[d->j] = remove_quotes_from_str(temp_string);
	if (!tokens[d->j])
	{
		free_n_string_array(tokens, d->j);
		free(temp_string);
		return (FAILURE);
	}
	free(temp_string);
	dprintf(2, "tokens[d->j]: %s\n\n", tokens[d->j]);
	d->j++;
	return (SUCCESS);
}


static void	set_start_and_increment_index(int *start, int *index, int increment)
{
	*start = *index;
	*index += increment;
}

/**
 * @brief Break down a string into individual tokens based on whitespace and 
 * quotes.
 * @param tokens Pointer to the array of strings where tokens will be stored.
 * @param str Pointer to the input string to tokenize.
 * @return int SUCCESS if tokenization is successful, FAILURE otherwise.
 */
int	assign_tokens(char **tokens, char const *str)
{
	t_index_data	d;

	initialise_index_data(&d);
	printf("ft_strlen(str): %d\n", ft_strlen(str));
	while (str[d.i])
	{
		while (ft_isspace(str[d.i]))
			d.i++;
		d.start = d.i;
		printf("starting arg at %d, str[%d]: %c\n", d.start, d.start, str[d.start]);

		while (str[d.i] && !isspace_outside_quotes(str[d.i], &d)
			&& !islinker_outside_quotes(&str[d.i], &d))
		{
//		printf("looping, i: %d, str[%d]: %c, d.n_sgl_quotes: %d, d.n_dbl_quotes: %d\n", d.i, d.i, str[d.i], d.n_sgl_quotes, d.n_dbl_quotes);
			if (str[d.i] == '\'' || str[d.i] == '\"')
				increase_quote_count_if_outside_quotes(str, d.i,
					&d.n_sgl_quotes, &d.n_dbl_quotes);
			d.i++;
		}
		if (d.n_sgl_quotes % 2 == 1 || d.n_dbl_quotes % 2 == 1)
			return (FAILURE);

//		printf("d.start: %d, d.i: %d, str[%d]: %c, sgl: %d, dbl: %d\n", d.start, d.i, d.i, str[d.i], d.n_sgl_quotes, d.n_dbl_quotes);
		if (d.start < d.i)
		{
			if (store_token(tokens, str, &d) == FAILURE)
				return (FAILURE);
		}
		else if (islinker_outside_quotes(&str[d.i], &d))
		{
			if (is_dbl_linker(&str[d.i]))
				set_start_and_increment_index(&d.start, &d.i, 2);
			else
				set_start_and_increment_index(&d.start, &d.i, 1);
			if (store_token(tokens, str, &d) == FAILURE)
				return (FAILURE);
		}
	}
	tokens[d.j] = NULL;
	return (SUCCESS);
}
