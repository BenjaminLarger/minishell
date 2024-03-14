/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/14 12:39:48 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	output_pipe_to_stdout(int fd)
{
	char	buffer[4096];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read < 0)
		{
			perror("read from pipe error");
			exit(EXIT_FAILURE);
		}
		write(STDOUT_FILENO, buffer, bytes_read);
	}
}

static void	exec_command(t_minishell *data, char **args, int start, int end)
{
	int			pid2;
	extern char	**environ;
	char		**env;
	char		*cmd_with_path;

	env = environ;
	pid2 = fork();
//	if (pid2 == -1)
//		display_error_and_exit("Fork error", commands);
	if (pid2 == 0)
	{
		dup2(data->fd_pipe1[READ_END], STDIN_FILENO);
		dup2(data->fd_pipe2[WRITE_END], STDOUT_FILENO); 
		close(data->fd_pipe1[READ_END]);
		close(data->fd_pipe2[WRITE_END]);

		args[end] = NULL;
		// SUCCESS, EXEC_FAIL (builtin exist, mais exec failed), NOT_BUILTIN
		if (exec_cmd_if_builtin(args, &start) == SUCCESS)
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (get_cmd_with_path(args[start], &cmd_with_path) == FAILURE)
				exit(EXIT_FAILURE); // check free
			dprintf(STDERR_FILENO, "cmd_with_path: %s\n", cmd_with_path); //
			execve(cmd_with_path, &(args[start]), env);
	//		handle_exec_error(args[start]);
			free(cmd_with_path);
			dprintf(STDERR_FILENO, "exec failed: %s\n", args[start]); // delete
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid2 > 0)
	{
		close(data->fd_pipe1[READ_END]);
		close(data->fd_pipe2[WRITE_END]);
		waitpid(pid2, NULL, 0);
	}
}

void	exec_args(t_minishell *data)
{
	int i = 0;
	int start_index = 0;

	print_array(data->args); //
	close(data->fd_pipe1[WRITE_END]);
	while (i < data->n_args && data->args[i]) // && data->args[i + 1])
	{
		start_index = i;
		while (data->args[i] && !is_linker(data->args[i]))
			i++; // linker now at index i, beginning of cmd at start_index
		dprintf(STDERR_FILENO, "\nlinker or eof at i = %d\n", i); //
		if (!data->args[i] || ft_strcmp(data->args[i], "|") == 0)
		{
			dprintf(STDERR_FILENO, "args[start_index]: %s\n", data->args[start_index]); //
			if (pipe(data->fd_pipe2) == -1)
				return ; // handle pipe error
			exec_command(data, data->args, start_index, i);
			data->fd_pipe1[READ_END] = data->fd_pipe2[READ_END];
		}
//		else
//			handle_redirection(&(data->args[i++]), data);
		i++;
	}
//	dprintf(STDERR_FILENO, "data->fd_pipe1[READ_END]: %d\n", data->fd_pipe1[READ_END]); //
//	check_open_fd(); // pour voir quels fd sont ouverts/fermés
	output_pipe_to_stdout(data->fd_pipe1[READ_END]);
	close(data->fd_pipe1[READ_END]);
}
