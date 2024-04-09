/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokens_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:36:58 by demre             #+#    #+#             */
/*   Updated: 2024/04/09 14:30:17 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks the syntax of an array of tokens. Print error if the prompt 
 * have a linker as last argument, a redirection followed by a pipe, or two 
 * consecutives pipes.
 * @return Returns SUCCESS if the syntax is valid, FAILURE otherwise.
 */
int	check_tokens_syntax(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (is_linker(args[i]) && !args[i + 1])
		{
			print_error_syntax(NULL);
			return (FAILURE);
		}
		else if ((is_redirection(args[i]) && is_linker(args[i + 1]))
			|| (!ft_strcmp(args[i], "|") && !ft_strcmp(args[i + 1], "|")))
		{
			print_error_syntax(args[i + 1]);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
