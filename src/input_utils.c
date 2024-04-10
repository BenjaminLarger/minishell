/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:51:27 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 16:21:01 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Increase quote count if the character is a quote, while not within
 * a pair of the opposite type of quotes.
 */
void	increase_quote_count_if_outside_quotes(char c,
	int *n_sgl_quotes, int *n_dbl_quotes)
{
	if (c == '\'' && *n_dbl_quotes % 2 == 0)
		(*n_sgl_quotes)++;
	else if (c == '\"' && *n_sgl_quotes % 2 == 0)
		(*n_dbl_quotes)++;
}

int	is_valid_ev_dollar_sign(char c, int *n_sgl_quotes, int *n_dbl_quotes,
	int *first_quote)
{
	increase_quote_count_if_outside_quotes(c, n_sgl_quotes,
		n_dbl_quotes);
	if (*n_sgl_quotes % 2 == 1 && *n_dbl_quotes % 2 == 0)
		*first_quote = single_quote;
	else if (*n_sgl_quotes % 2 == 0 && *n_dbl_quotes % 2 == 1)
		*first_quote = double_quote;
	else
		*first_quote = no_quote;
	if (*first_quote != 1 && c == '$')
		return (TRUE);
	return (FALSE);
}

int	is_redirection(char *str)
{
	if (ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0
	)
		return (TRUE);
	return (FALSE);
}
