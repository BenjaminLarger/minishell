/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_assign_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:01:44 by demre             #+#    #+#             */
/*   Updated: 2024/03/02 21:13:13 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialise variables used in the index-related data structure.
 * @param t Pointer to the index data structure to be initialised.
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
 * @brief Increase the count of single or double quotes based on the type 
 * specified.
 * @param d Pointer to the index data structure containing quote counts.
 * @param type_of_quotes Type of quotes to increase count (single_quote or 
 * double_quote).
 */
static void	increase_quote_count(t_index_data *d, enum e_quote type_of_quotes)
{
	if (type_of_quotes == single_quote)
		d->n_sgl_quotes++;
	else if (type_of_quotes == double_quote)
		d->n_dbl_quotes++;
	d->i++;
}

/**
 * @brief Store a token extracted from the input string into the tokens array.
 * This function extracts a substring from the input string based on start and 
 * end indices, allocates memory for it, and stores it in the tokens array.
 * @param tokens Pointer to the array of strings where tokens will be stored.
 * @param str Pointer to the input string.
 * @param d Pointer to the index data structure containing indices and quote counts.
 * @return int SUCCESS if storing the token is successful, FAILURE otherwise.
 */
static int	store_token(char **tokens, char const *str, t_index_data *d)
{
// Option not to include quotes when saving token
//	if ((str[d->start] == '\'' && str[d->i - 1] == '\'')
//		|| (str[d->start] == '\"' && str[d->i - 1] == '\"'))
//		tokens[d->j] = ft_substr(str, d->start + 1, (d->i - d->start - 2));
//	else
	tokens[d->j] = ft_substr(str, d->start, (d->i - d->start));
	if (!tokens[d->j])
	{
		free_n_string_array(tokens, d->j);
		return (FAILURE);
	}
	d->j++;
	return (SUCCESS);
}

/**
 * @brief Move the index to the next non-whitespace character outside of quotes.
 * @param str Pointer to the input string.
 * @param d Pointer to the index data structure containing indices and quote 
 * counts.
 */
static void	find_next_non_whitespace_outside_quotes(char const *str,
	t_index_data *d)
{
	while (str[d->i]
		&& ((d->n_sgl_quotes % 2 == 0 && d->n_dbl_quotes % 2 == 0
				&& !ft_isspace(str[d->i]))
			|| (d->n_sgl_quotes % 2 == 1 && str[d->i] != '\'')
			|| (d->n_dbl_quotes % 2 == 1 && str[d->i] != '\"'))
	)
		d->i++;
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
	while (str[d.i])
	{
		while (ft_isspace(str[d.i]))
			d.i++;
		d.start = d.i;
		if (str[d.i] == '\'')
			increase_quote_count(&d, single_quote);
		else if (str[d.i] == '\"')
			increase_quote_count(&d, double_quote);
		find_next_non_whitespace_outside_quotes(str, &d);
		if (d.n_sgl_quotes % 2 == 1 && str[d.i] == '\'')
			increase_quote_count(&d, single_quote);
		else if (d.n_dbl_quotes % 2 == 1 && str[d.i] == '\"')
			increase_quote_count(&d, double_quote);
//		printf("d.start: %d, %c ", d.start, str[d.start]);
//		printf("d.i: %d, %c, sgl: %d, dbl: %d\n", d.i, str[d.i], d.n_sgl_quotes, d.n_dbl_quotes);
		if (d.n_sgl_quotes % 2 == 1 || d.n_dbl_quotes % 2 == 1)
			return (FAILURE);
//		printf("d.start: %d, %c, d.i: %d, %c\n", d.start, str[d.start], d.i, str[d.i]);
		if (d.start < d.i)
			if (store_token(tokens, str, &d) == FAILURE)
				return (FAILURE);
	}
	tokens[d.j] = NULL;
	return (SUCCESS);
}
