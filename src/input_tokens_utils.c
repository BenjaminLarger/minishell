/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:35:59 by demre             #+#    #+#             */
/*   Updated: 2024/03/25 20:14:30 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sgl_linker(char const *str)
{
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (TRUE);
	return (FALSE);
}

int	is_dbl_linker(char const *str)
{
	if ((str[0] == '>' && str[1] && str[1] == '>')
		|| (str[0] == '<' && str[1] && str[1] == '<')
	)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Checks if the character is a whitespace and outside quotes.
 */
int	isspace_outside_quotes(int c, t_index_data *ind)
{
	if (ft_isspace(c)
		&& (ind->n_sgl_quotes % 2 == 0 && ind->n_dbl_quotes % 2 == 0))
		return (TRUE);
	else
		return (FALSE);
}

/**
 * @brief Checks if the character is a linker ('|', '<', '>', '<<', '>>') and
 * outside quotes.
 */
int	islinker_outside_quotes(char const *str, t_index_data *ind)
{
	if (
		(ind->n_sgl_quotes % 2 == 0 && ind->n_dbl_quotes % 2 == 0)
		&& (is_dbl_linker(str) || is_sgl_linker(str))
	)
		return (TRUE);
	else
		return (FALSE);
}

int	is_outside_quotes(t_token_data *tok)
{
	if (tok->n_sgl_quotes % 2 == 0 && tok->n_dbl_quotes % 2 == 0)
		return (TRUE);
	else
		return (FALSE);
}
