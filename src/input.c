/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:16 by demre             #+#    #+#             */
/*   Updated: 2024/03/05 16:54:31 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prompt user for input => readline function => download readline
// Add each line to the history (global variable ?)
// Handle whitespace
// History => Type a command line, then use ctrl-C and press "Enter". The buffer should be clean and there should be nothing left to execute.
// Can we navigate through history using Up and Down? Can we retry some command?
// Execute commands that should not work like 'dsbksdgbksdghsd'. Ensure minishell doesn't crash and prints an error.
// 'cat | cat | ls' should behave in a "normal way".
// Try to execute a long command with a ton of arguments.
// handle empty value
// Handle only space or tab
// If readline read an empty line => return NULL 

char	*read_input(char *prompt)
{
	if (prompt)
	{
		free(prompt);
		prompt = NULL;
	}
	prompt = readline("minish> ");
	if (prompt && *prompt)
		add_history(prompt);
	return (prompt);
}

/**
 * @brief Split the prompt string into strings saved in a args array
 * @param t_minishell Structure representing the shared data and parameters.
 * @return 
 */
int		split_input_into_args(t_minishell *data)
{
	int		n_args;

	n_args = count_tokens(data->prompt);
//	printf("%s, n_args: %d\n", data->prompt, n_args); //
	data->args = (char **)malloc((n_args + 1) * sizeof(char *));
	if (!data->args)
		return (FAILURE);
	if (data->prompt && assign_tokens(data->args, data->prompt) == FAILURE)
		return (FAILURE);

	// print_array(data->args);
	
	return (SUCCESS);
}
