/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:51:27 by demre             #+#    #+#             */
/*   Updated: 2024/03/20 16:23:37 by demre            ###   ########.fr       */
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
int	isspace_outside_quotes(int c, t_index_data *d)
{
	if (ft_isspace(c) && (d->n_sgl_quotes % 2 == 0 && d->n_dbl_quotes % 2 == 0))
		return (TRUE);
	else
		return (FALSE);
}

/**
 * @brief Checks if the character is a linker ('|', '<', '>', '<<', '>>') and
 * outside quotes.
 */
int	islinker_outside_quotes(char const *str, t_index_data *d)
{
	if (
		(d->n_sgl_quotes % 2 == 0 && d->n_dbl_quotes % 2 == 0)
		&& (is_dbl_linker(str) || is_sgl_linker(str))
	)
		return (TRUE);
	else
		return (FALSE);
}
