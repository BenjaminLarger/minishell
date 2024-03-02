/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:49 by demre             #+#    #+#             */
/*   Updated: 2024/03/02 13:15:14 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	pid_t	pid1;

	if (argc != 1 && argv && (envp || !envp))
		return (EXIT_FAILURE);
//		return (print_error(ARG), exit(EXIT_FAILURE));

	prompt = NULL;
	pid1 = fork();
	if (pid1 == -1)
		return (EXIT_FAILURE);//		error_and_exit(commands);
	else if (pid1 == 0)
		handle_prompt(&prompt);
	else if (pid1 > 0)
	{
		waitpid(pid1, NULL, 0);
	}
	return (EXIT_SUCCESS);
}
