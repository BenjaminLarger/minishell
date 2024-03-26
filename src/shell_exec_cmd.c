/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/03/26 13:42:59 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_minishell *data, char **cmd, int **pid, int *n_pid)
{
	char		*cmd_with_path;
//	int			pid2;
//	int			status;

	if (is_env_changing_builtin(cmd, data) == TRUE)
		return ;
	data->executed_command = TRUE;
	print_array(cmd);
	if (pipe(data->fd_pipe2) == -1)
		return ; // handle pipe error
	dprintf(2, "\n*n_pid: %d\n", *n_pid); //
	(*pid)[*n_pid] = fork();
//	if (*pid[*n_pid] == -1)
//		display_error_and_exit("Fork error", commands);
	if ((*pid)[*n_pid] == 0)
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
		if (get_cmd_with_path(data, cmd[0], &cmd_with_path) == FAILURE)
			exit(EXIT_FAILURE); // check free
		dprintf(STDERR_FILENO, "cmd_with_path: %s\n", cmd_with_path); //
		execve(cmd_with_path, &(cmd[0]), data->env_msh);
		free(cmd_with_path);
		print_error_cmd(cmd[0]);
		exit(127); //send exit error status 
	}
	else if ((*pid)[*n_pid] > 0)
	{
		(*n_pid)++;
		close(data->fd_pipe1[READ_END]);
		close(data->fd_pipe2[WRITE_END]);
		data->fd_pipe1[READ_END] = data->fd_pipe2[READ_END];
	}
}
