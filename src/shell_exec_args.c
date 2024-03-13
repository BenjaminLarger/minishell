/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/13 13:18:12 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_minishell *data, char **args, int start, int end, int fd)
{
	int			pid2;
	extern char	**environ;
	char		**env;

	env = environ;
	pid2 = fork();
//	if (pid2 == -1)
//		display_error_and_exit("Fork error", commands);
	if (pid2 == 0)
	{
		args[end] = NULL;

		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(data->fd_pipe1[1], STDOUT_FILENO); // WRITE_END
		close(data->fd_pipe1[0]); // READ_END
		close(data->fd_pipe1[1]); // WRITE_END
//		dprintf(STDERR_FILENO, "executing: %s from %d to %d\n", args[start], start, end); // delete

		char *test[2];
		test[0] = "/bin/ls";
		test[1] = NULL;
		dprintf(STDERR_FILENO, "executing: %s from %d to %d\n", test[0], start, end); // delete
		execve(test[0], test, env); // add envp
		dprintf(STDERR_FILENO, "exec failed: %s\n", test[0]); // delete

		execve(args[start], &(args[start]), env); // add envp
//		handle_exec_error(args[start]);
//		dprintf(STDERR_FILENO, "exec failed: %s\n", args[start]); // delete
		perror("execve error");
		exit(EXIT_FAILURE);
	}
	else if (pid2 > 0)
	{
		close(data->fd_pipe1[1]); // READ_END
		close(fd);
		waitpid(pid2, NULL, 0);
	}
}

void	exec_args(t_minishell *data)
{
	int i = 0;
	int start_index = 0;
	int fd_in;

	print_array(data->args);
	fd_in = dup(STDIN_FILENO);
	while (i < data->n_args && data->args[i] && data->args[i + 1])
	{
		start_index = i;
		while (data->args[i] && !is_linker(data->args[i]))
			i++; // linker now at index i, beginning of cmd at start_index
		dprintf(STDERR_FILENO, "linker or eof at i: %d\n", i); //
		if (!data->args[i] || ft_strcmp(data->args[i], "|") == 0)
		{
			dprintf(STDERR_FILENO, "args[start_index]: %s\n", data->args[start_index]); //
			if (pipe(data->fd_pipe1) == -1)
				return ; // handle error
	//			display_error_and_exit("Pipe error", commands);
			exec_command(data, data->args, start_index, i, fd_in);
			fd_in = data->fd_pipe1[0]; // update to READ_END, input for next cmd
		}
	//	else if ("<")
	//		arg i +1 est un fichier
		i++;
		dprintf(STDERR_FILENO, "end loop with i: %d\n", i); //
	}
	close(fd_in);
}
