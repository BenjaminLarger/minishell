/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_handle_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/02 12:15:25 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	initialise_word_data(t_word_data *v)
{
	v->n_words = 0;
	v->i = 0;
	v->inside_word = 1;
	v->n_quotes = 0;
}

static int	count_words(char const *s, char c)
{
	t_word_data	w;

	initialise_word_data(&w);
	while (s[w.i] != '\0')
	{
		if (s[w.i] == '\'')
			w.n_quotes++;
		if (w.i == 0 && s[w.i] != c)
			w.n_words++;
		else if (s[w.i] == c && w.n_quotes % 2 == 0)
			w.inside_word = 0;
		else if (w.inside_word == 0)
		{
			w.inside_word = 1;
			w.n_words++;
		}
		w.i++;
	}
	if (w.n_quotes % 2 == 1)
		w.n_words = 0;
	return (w.n_words);
}
 */
/* 
int	count_tokens(char *str)
{
	int	n_tokens;

	if (!str || str[0] == '\0')
		n_tokens = 0;
	else if (str && ft_strlen(str) > 0 && ft_strchr(str, ' ') == NULL)
		n_tokens = 1;
	else
		n_tokens = count_words(str, ' ');
	return (n_tokens);
}
 */
/**
 * 
 */
int	handle_prompt(char *prompt)
{
		printf("%s, %zu\n", prompt, ft_strlen(prompt));

	return (SUCCESS);
}