/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:49 by demre             #+#    #+#             */
/*   Updated: 2024/03/25 19:44:03 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
//	int			status;

	if (argc != 1 && argv)
		return (EXIT_FAILURE); // "wrong arg number"
	data.cd_last_dir = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
	if (!data.cd_last_dir)
			return (0); //we can move it // to free
	
	if (pipe(data.fd_pipe1) == -1)
		return (EXIT_FAILURE); //	"Pipe error"
//	data.pid1 = fork();
//	if (data.pid1 == -1)
//		return (EXIT_FAILURE); //	"Fork error"
//	else if (data.pid1 == 0)
	
	malloc_env_variables(&data, envp);
	printf("ft_getenv(SHLVL): %s\n", ft_getenv(&data, "SHLVL"));

	run_shell_loop(&data);


//	else if (data.pid1 > 0)
/* 	{
		signal_handling(&data);
		waitpid(data.pid1, &status, 0);

		if (WIFEXITED(status))
		{
			data.last_exit_status = WEXITSTATUS(status); //$? handle
			dprintf(2, "last exit status in grand parent = %d\n", data.last_exit_status);
			int exit_status = WEXITSTATUS(status);
			if (exit_status == 0) {
				printf("Child process terminated successfully. Parent process exiting.\n");
			} else {
				printf("Child process terminated with error (exit status: %d). Parent process continuing.\n", exit_status);
			}
		} else {
			data.last_exit_status = 0; //$? handle
			printf("Child process terminated abnormally. Parent process continuing.\n");
		}
	} */
	free_string_array(data.env_msh);
	return (EXIT_SUCCESS);
}
