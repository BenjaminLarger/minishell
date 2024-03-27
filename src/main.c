/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:49 by demre             #+#    #+#             */
/*   Updated: 2024/03/27 14:29:12 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	if (argc != 1 && argv)
		exit(EXIT_SUCCESS);
//	ft_memset(&data, 0, sizeof(t_minishell));
//	check_open_fd("\e[35mstartup\e[0m");
//	print_pipes_fd(&data);
//	for (int fd = 3; fd <= 10; fd++) {
//		if (fcntl(fd, F_GETFD) != -1)
//			close(fd);
//	}

	if (load_env_variables(&data, envp) == FAILURE
		|| init_program(&data) == FAILURE)
		exit(EXIT_FAILURE);
	dprintf(2, "\e[36mLaunching minishell - $SHLVL=%s\e[0m\n", ft_getenv(&data, "SHLVL"));
//	if (pipe(data.fd_pipe1) == -1)
//		return (print_error_and_failure(PIPE));
//	close(data.fd_pipe1[WRITE_END]);
//	print_pipes_fd(&data);

	run_shell_loop(&data);

	free_string_array(data.env_msh);
//	free(data.cd_last_dir);
	exit(EXIT_SUCCESS);
}

//	int			status;
//	data.pid1 = fork();
//	if (data.pid1 == -1)
//		return (EXIT_FAILURE); //	"Fork error"
//	else if (data.pid1 == 0)
/* 	else if (data.pid1 > 0)
	{
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
	}
 */