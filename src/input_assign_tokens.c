/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_assign_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:01:44 by demre             #+#    #+#             */
/*   Updated: 2024/03/02 16:17:45 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialise_index_data(t_index_data *v)
{
	v->i = 0;
	v->j = 0;
	v->start = 0;
	v->n_sgl_quotes = 0;
	v->n_dbl_quotes = 0;
}

static void	increase_n_quotes(t_index_data *v, int type_of_quotes)
{
	if (type_of_quotes == 1)
		v->n_sgl_quotes++;
	else if (type_of_quotes == 2)
		v->n_dbl_quotes++;
	v->i++;
}

static int	split_string(char **tokens, char *str, t_index_data *v)
{
// Don't include quotes when saving token
//	if ((str[v->start] == '\'' && str[v->i - 1] == '\'')
//		|| (str[v->start] == '\"' && str[v->i - 1] == '\"'))
//		tokens[v->j] = ft_substr(str, v->start + 1, (v->i - v->start - 2));
//	else
		tokens[v->j] = ft_substr(str, v->start, (v->i - v->start));
	if (!tokens[v->j])
	{
		free_n_string_array(tokens, v->j);
		return (FAILURE);
	}
	v->j++;
	return (SUCCESS);
}

static void	walk_the_string(char *str, t_index_data *v)
{
	while (str[v->i]
		&& ((v->n_sgl_quotes % 2 == 0 && v->n_dbl_quotes % 2 == 0
				&& !ft_isspace(str[v->i]))
			|| (v->n_sgl_quotes % 2 == 1 && str[v->i] != '\'')
			|| (v->n_dbl_quotes % 2 == 1 && str[v->i] != '\"'))
	)
		v->i++;
}

char	**assign_tokens(char **tokens, char *str)
{
	t_index_data	v;

	initialise_index_data(&v);
	while (str[v.i])
	{
		while (ft_isspace(str[v.i]))
			v.i++;
		v.start = v.i;
		if (str[v.i] == '\'')
			increase_n_quotes(&v, 1);
		else if (str[v.i] == '\"')
			increase_n_quotes(&v, 2);
		walk_the_string(str, &v);
		if (v.n_sgl_quotes % 2 == 1 && str[v.i] == '\'')
			increase_n_quotes(&v, 1);
		else if (v.n_dbl_quotes % 2 == 1 && str[v.i] == '\"')
			increase_n_quotes(&v, 2);
//		printf("v.start: %d, %c ", v.start, str[v.start]);
//		printf("v.i: %d, %c, sgl: %d, dbl: %d\n", v.i, str[v.i], v.n_sgl_quotes, v.n_dbl_quotes);
		if (v.n_sgl_quotes % 2 == 1 || v.n_dbl_quotes % 2 == 1)
			return (NULL);
//		printf("v.start: %d, %c, v.i: %d, %c\n", v.start, str[v.start], v.i, str[v.i]);
		if (v.start < v.i)
			if (split_string(tokens, str, &v) == FAILURE)
				return (NULL);
	}
	tokens[v.j] = NULL;
	return (tokens);
}
