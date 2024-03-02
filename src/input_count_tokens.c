/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_count_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:01:55 by demre             #+#    #+#             */
/*   Updated: 2024/03/02 16:30:27 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialise_word_data(t_word_data *v)
{
	v->n_words = 0;
	v->i = 0;
	v->inside_word = TRUE;
	v->n_sgl_quotes = 0;
	v->n_dbl_quotes = 0;
}

static int	count_words(char const *str)
{
	t_word_data	w;

	initialise_word_data(&w);
	while (str[w.i])
	{
		if (str[w.i] == '\'' && w.n_dbl_quotes % 2 == 0)
			w.n_sgl_quotes++;
		else if (str[w.i] == '\"' && w.n_sgl_quotes % 2 == 0)
			w.n_dbl_quotes++;
		if (w.i == 0 && !ft_isspace(str[w.i]))
			w.n_words++;
		else if (ft_isspace(str[w.i])
			&& w.n_sgl_quotes % 2 == 0 && w.n_dbl_quotes % 2 == 0)
			w.inside_word = FALSE;
		else if (w.inside_word == FALSE)
		{
			w.inside_word = TRUE;
			w.n_words++;
		}
		w.i++;
	}
	if (w.n_sgl_quotes % 2 == 1 || w.n_dbl_quotes % 2 == 1)
		w.n_words = 0;
	return (w.n_words);
}

int	count_tokens(char *str)
{
	int	n_tokens;

	if (!str || str[0] == '\0')
		n_tokens = 0;
	else if (str && ft_strlen(str) > 0 && ft_strchr(str, ' ') == NULL)
		n_tokens = 1;
	else
		n_tokens = count_words(str);
	return (n_tokens);
}
