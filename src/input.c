/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:16 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 17:53:21 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Reads user input from the command line. The input is added to the 
 * history if it is not empty.
 * @return Returns a pointer to the string containing the user input.
 */
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
 * @return Returns SUCCESS if no prompt or if the prompt has been split into 
 * tokens correctly, FAILURE otherwise.
 */
int	split_input_into_args(t_minishell *data)
{
	data->n_args = count_tokens(data->prompt);
	printf("%s, n_args: %d\n", data->prompt, data->n_args); //
	if (data->n_args == 0)
		return (SUCCESS);
	else if (data->n_args == -1)
	{
		data->last_exit_status = 1;
		return (FAILURE);
	}
	data->args = (char **)malloc((data->n_args + 1) * sizeof(char *));
	if (!data->args)
	{
		data->last_exit_status = 1;
		return (print_error_and_failure(MALLOC_FAIL));
	}
	if (data->prompt)
	{
		if (assign_tokens(data, data->prompt) != SUCCESS)
		{
			data->last_exit_status = 1;
			return (print_error_and_failure(MALLOC_FAIL));
		}
	}
	return (SUCCESS);
}
