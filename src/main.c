/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:49 by demre             #+#    #+#             */
/*   Updated: 2024/03/03 12:49:43 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	pid_t	pid1;

	if (argc != 1 && argv && (envp || !envp))
		return (EXIT_FAILURE);
//		return (print_error(ARG), exit(EXIT_FAILURE));

	pid1 = fork();
	if (pid1 == -1)
		return (EXIT_FAILURE);//		error_and_exit(commands);
	else if (pid1 == 0)
		run_shell_loop(&data);
	else if (pid1 > 0)
	{
		signal_handling(pid1);
		waitpid(pid1, NULL, 0);
	}
	return (EXIT_SUCCESS);
}
