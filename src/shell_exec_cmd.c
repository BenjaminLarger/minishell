/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/03/18 16:50:08 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_minishell *data, char **cmd)
{
	int			pid2;
	extern char	**environ;
	char		**env;
	char		*cmd_with_path;
	
	print_array(cmd); //
	env = environ;
	if (pipe(data->fd_pipe2) == -1)
		return ; // handle pipe error
	pid2 = fork();
//	if (pid2 == -1)
//		display_error_and_exit("Fork error", commands);
	if (pid2 == 0)
	{
		dup2(data->fd_pipe1[READ_END], STDIN_FILENO);
		dup2(data->fd_pipe2[WRITE_END], STDOUT_FILENO); 
		close(data->fd_pipe1[READ_END]);
		close(data->fd_pipe2[WRITE_END]);

		// SUCCESS, EXEC_FAIL (builtin exist, mais exec failed), NOT_BUILTIN
		if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
			exit(EXIT_SUCCESS);
		else
		{
			if (get_cmd_with_path(cmd[0], &cmd_with_path) == FAILURE)
				exit(EXIT_FAILURE); // check free
			dprintf(STDERR_FILENO, "cmd_with_path: %s\n", cmd_with_path); //
			execve(cmd_with_path, &(cmd[0]), env);
	//		handle_exec_error(cmd[0]);
			free(cmd_with_path);
			print_error_cmd(cmd[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid2 > 0)
	{
		close(data->fd_pipe1[READ_END]);
		close(data->fd_pipe2[WRITE_END]);
		waitpid(pid2, NULL, 0);
		data->fd_pipe1[READ_END] = data->fd_pipe2[READ_END];
	}
}
