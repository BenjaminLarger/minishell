/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_read_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:16 by demre             #+#    #+#             */
/*   Updated: 2024/03/02 19:59:07 by demre            ###   ########.fr       */
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

/**
 * @brief Split the prompt string into strings saved in a token array
 * @param prompt 
 * @return 
 */
int	process_input(char **prompt)
{
	char	**tokens;
	int		n_tokens;

	n_tokens = count_tokens(*prompt);
	if (n_tokens == 0)
		return (FAILURE);
	printf("%s, n_tokens: %d\n", *prompt, n_tokens); //
	tokens = (char **)malloc((n_tokens + 1) * sizeof(char *));
	if (!tokens)
		return (FAILURE);
	if (assign_tokens(tokens, *prompt) == FAILURE)
		return (FAILURE);

// Print all tokens in terminal
	int i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	
	return (SUCCESS);
}

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
