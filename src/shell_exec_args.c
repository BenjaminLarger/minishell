/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/14 14:42:36 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//close(data->fd_pipe1[WRITE_END]);
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
		dprintf(STDERR_FILENO, "\npipes_fd\n", i); //
			print_pipes_fd(data);
		}
		else
		{
			handle_redirection(&(data->args[i++]), data);
			// < infile
			// fd_file = open(infile)
			// data->fd_pipe1[READ_END] = fd_file;
		}
		i++;
	}
//	dprintf(STDERR_FILENO, "data->fd_pipe1[READ_END]: %d\n", data->fd_pipe1[READ_END]); //
//	check_open_fd(); // pour voir quels fd sont ouverts/fermés
	write_fdin_to_fdout(data->fd_pipe1[READ_END], STDOUT_FILENO);
}
