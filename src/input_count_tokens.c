/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_count_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:01:55 by demre             #+#    #+#             */
/*   Updated: 2024/03/22 18:40:53 by demre            ###   ########.fr       */
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

static void	handle_two_character_linker(t_token_data *t)
{
	t->is_inside_token = FALSE;
	t->n_tokens++;
	t->i++;
}

static void	handle_one_character_linker(t_token_data *t)
{
	t->is_inside_token = FALSE;
	t->n_tokens++;
}

static void	handle_new_token(t_token_data *t)
{
	t->is_inside_token = TRUE;
	t->n_tokens++;
}

int	count_tokens(char const *str)
{
	t_token_data	t;
	
	initialise_token_data(&t);
	if (!str || str[0] == '\0')
		return (0);
	while (str[t.i])
	{
		increase_quote_count_if_outside_quotes(str, t.i, &t.n_sgl_quotes,
			&t.n_dbl_quotes);
		if (is_dbl_linker(&str[t.i]) && is_outside_quotes(&t))
			handle_two_character_linker(&t);
		else if (is_sgl_linker(&str[t.i]) && is_outside_quotes(&t))
			handle_one_character_linker(&t);
		else if (ft_isspace(str[t.i]) && is_outside_quotes(&t))
			t.is_inside_token = FALSE;
		else if (t.i == 0 && !ft_isspace(str[t.i]))
			t.n_tokens++;
		else if (t.is_inside_token == FALSE)
			handle_new_token(&t);
		t.i++;
	}
	if (t.n_sgl_quotes % 2 == 1 || t.n_dbl_quotes % 2 == 1)
		t.n_tokens = 0;
	return (t.n_tokens);
}
