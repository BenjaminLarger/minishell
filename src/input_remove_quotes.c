/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_remove_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:29:08 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 16:00:49 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculate_no_quote_str_length(char *with_quote)
{
	int		no_quote_len;
	int		n_sgl_quotes;
	int		n_dbl_quotes;
	int		i;

	no_quote_len = 0;
	n_sgl_quotes = 0;
	n_dbl_quotes = 0;
	i = 0;
	while (with_quote[i])
	{
		if (with_quote[i] == '\'' && n_dbl_quotes % 2 == 0)
			n_sgl_quotes++;
		else if (with_quote[i] == '\"' && n_sgl_quotes % 2 == 0)
			n_dbl_quotes++;
		i++;
	}
	no_quote_len = ft_strlen(with_quote) - n_sgl_quotes - n_dbl_quotes;
	return (no_quote_len);
}

static void	loop_and_remove_quotes(char *with_quote, char **no_quote)
{
	int		no_q_idx;
	int		with_q_idx;
	int		n_sgl_quotes;
	int		n_dbl_quotes;

	no_q_idx = 0;
	with_q_idx = 0;
	n_sgl_quotes = 0;
	n_dbl_quotes = 0;
	while (with_quote[with_q_idx])
	{
		if (with_quote[with_q_idx] == '\'' && n_dbl_quotes % 2 == 0)
		{
			n_sgl_quotes++;
			with_q_idx++;
		}
		else if (with_quote[with_q_idx] == '\"' && n_sgl_quotes % 2 == 0)
		{
			n_dbl_quotes++;
			with_q_idx++;
		}
		else
			(*no_quote)[no_q_idx++] = with_quote[with_q_idx++];
	}
	(*no_quote)[no_q_idx] = '\0';
}

char	*remove_quotes_from_str(char *with_quote)
{
	char	*no_quote;
	int		no_quote_len;	

	no_quote_len = calculate_no_quote_str_length(with_quote);
	no_quote = (char *)malloc((no_quote_len + 1) * sizeof(char));
	if (!no_quote)
		return (NULL);
	loop_and_remove_quotes(with_quote, &no_quote);
	return (no_quote);
}
