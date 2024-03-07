/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:49 by demre             #+#    #+#             */
/*   Updated: 2024/03/06 17:23:01 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;

int	main(int argc, char **argv)
{
	t_minishell	data;
	int			status; // prob to delete

	if (argc != 1 && argv)
		return (EXIT_FAILURE);
//		return (print_error(ARG), exit(EXIT_FAILURE));
	data.cd_last_dir = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
	if (!data.cd_last_dir)
			return (0); //we can move it // to free
	data.pid1 = fork();
	if (data.pid1 == -1)
		return (EXIT_FAILURE);//		error_and_exit(commands);
	else if (data.pid1 == 0)
		run_shell_loop(&data);
	else if (data.pid1 > 0)
	{
		signal_handling(&data, &status);
		waitpid(data.pid1, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
			printf("Child process terminated successfully. Parent process exiting.\n");
		} else {
			printf("Child process terminated with error. Parent process continuing.\n");
		}
	}
	return (EXIT_SUCCESS);
}