/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_count_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:01:55 by demre             #+#    #+#             */
/*   Updated: 2024/03/20 17:55:03 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialise variables used in the token-related data structure.
 * @param t Pointer to the token data structure to be initialised.
 */
static void	initialise_token_data(t_token_data *t)
{
	t->n_tokens = 0;
	t->i = 0;
	t->is_inside_token = TRUE;
	t->n_sgl_quotes = 0;
	t->n_dbl_quotes = 0;
}

/**
 * @brief Increase quote count if the character is a quote.
 * This function increases the count of single or double quotes based on the 
 * character encountered in the string, while ensuring that the quote is not 
 * within a pair of the opposite type of quotes.
 */
static void	increase_quote_count_if_outside_quotes(char const *str,
	t_token_data *t)
{
	if (str[t->i] == '\'' && t->n_dbl_quotes % 2 == 0)
		t->n_sgl_quotes++;
	else if (str[t->i] == '\"' && t->n_sgl_quotes % 2 == 0)
		t->n_dbl_quotes++;
}

static int	is_outside_quotes(int c, t_token_data *t)
{
	if (c && t->n_sgl_quotes % 2 == 0 && t->n_dbl_quotes % 2 == 0)
		return (TRUE);
	else
		return (FALSE);
}

int	count_tokens(char const *str)
{
	t_token_data	t;

	initialise_token_data(&t);
	if (!str || str[0] == '\0')
		return (0);
	while (str[t.i])
	{
		increase_quote_count_if_outside_quotes(str, &t);
		if (t.i == 0 && !ft_isspace(str[t.i]))
			t.n_tokens++;
		else if (ft_isspace(str[t.i])
			&& t.n_sgl_quotes % 2 == 0 && t.n_dbl_quotes % 2 == 0)
			t.is_inside_token = FALSE;
		else if (is_outside_quotes(str[t.i], &t) && is_dbl_linker(&str[t.i]))
		{
			t.is_inside_token = FALSE;
			t.n_tokens++;
		}
		else if (is_outside_quotes(str[t.i], &t) && is_sgl_linker(&str[t.i]))
		{
			t.is_inside_token = FALSE;
			t.n_tokens++;
			t.i++;
		}
		else if (t.is_inside_token == FALSE)
		{
			t.is_inside_token = TRUE;
			t.n_tokens++;
		}
		t.i++;
	}
	// Handle if there's an odd number of quotes
	if (t.n_sgl_quotes % 2 == 1 || t.n_dbl_quotes % 2 == 1)
		t.n_tokens = 0;
	return (t.n_tokens);
}
