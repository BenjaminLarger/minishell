/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:16 by demre             #+#    #+#             */
/*   Updated: 2024/04/03 20:13:07 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input(char *prompt)
{
	if (prompt)
	{
		free(prompt);
		prompt = NULL;
	}
	prompt = readline("\e[32mminish> \e[0m");
//	prompt = readline("minish> ");
	if (prompt && *prompt)
		add_history(prompt);
	return (prompt);
}

/**
 * @brief Split the prompt string into strings saved in a args array
 * @param t_minishell Structure representing the shared data and parameters.
 * @return 
 */
int	split_input_into_args(t_minishell *data)
{
	int	error;

	data->n_args = count_tokens(data->prompt);
	printf("%s, n_args: %d\n", data->prompt, data->n_args); //
	if (data->n_args == 0)
		return (SUCCESS);
	else
		data->args = (char **)malloc((data->n_args + 1) * sizeof(char *));
	if (!data->args)
		return (errno); // ERR_MALLOC
	if (data->prompt)
	{
		error = assign_tokens(data, data->prompt);
		if (error != SUCCESS)
			return (error); // ERR_SINGLE_QUOTE or ERR_MALLOC, not implemented
	}
//	print_array(data->args);
	return (SUCCESS);
}
