/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/03/25 16:49:18 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_minishell *data, char **cmd)
{
	int			pid2;
	extern char	**environ;
	char		**env;
	char		*cmd_with_path;
	int			status;

	status = 0;
	if (is_env_changing_builtin(cmd, data) == TRUE)
		return ;
	data->executed_command = TRUE;
	print_array(cmd);
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
		if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
		{
			exit(data->last_exit_status);
		}
		// SUCCESS, EXEC_FAIL (builtin exist, mais exec failed), NOT_BUILTIN
		if (get_cmd_with_path(cmd[0], &cmd_with_path) == FAILURE)
			exit(EXIT_FAILURE); // check free
		dprintf(STDERR_FILENO, "cmd_with_path: %s\n", cmd_with_path); //
		execve(cmd_with_path, &(cmd[0]), env);
		free(cmd_with_path);
		print_error_cmd(cmd[0]);
		exit(127); //send exit error status 
	}
	else if (pid2 > 0)
	{
		close(data->fd_pipe1[READ_END]);
		close(data->fd_pipe2[WRITE_END]);
		dprintf(2, "waiting for pid2\n");
		waitpid(pid2, &status, 0);
		dprintf(2, "done waiting for pid2\n");
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
			{
				dprintf(2, "errno exit status in first child = %d\n", (WEXITSTATUS(status)));
				data->last_exit_status = WEXITSTATUS(status);
				//data->last_exit_status = 127;
			}
		}
		dprintf(2, "errno exit status in first child = %d\n", (WEXITSTATUS(status)));
		data->fd_pipe1[READ_END] = data->fd_pipe2[READ_END];
	}
}
