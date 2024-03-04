/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:49 by demre             #+#    #+#             */
/*   Updated: 2024/03/04 21:37:31 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_unblock_sigquit = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	int			status;

	g_unblock_sigquit = 0;
	if (argc != 1 && argv && (envp || !envp))
		return (EXIT_FAILURE);
//		return (print_error(ARG), exit(EXIT_FAILURE));

	data.pid1 = fork();
	if (data.pid1 == -1)
		return (EXIT_FAILURE);//		error_and_exit(commands);
	else if (data.pid1 == 0)
		run_shell_loop(&data);
	else if (data.pid1 > 0)
	{
		printf("From parent, pid: %d\n", getpid()); //
		set_child_ctr_d_action();
		signal_handling(data.pid1, &status);
		printf("waiting\n");
		waitpid(data.pid1, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
			printf("Child process terminated successfully. Parent process exiting.\n");
		} else {
			printf("Child process terminated with error. Parent process continuing.\n");
		}
	}
	return (EXIT_SUCCESS);
}
