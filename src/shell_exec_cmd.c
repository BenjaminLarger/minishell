/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/04/03 21:07:39 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_minishell *data, char **cmd, int end_index)
{
	char	*cmd_with_path;

	dprintf(2, "\ncurrent last, data->args[%d]: %s\n", end_index, data->args[end_index]); //
	if (is_env_changing_builtin(cmd, data) == TRUE)
		return ; // handle?

	data->executed_command = TRUE;
	print_array(cmd, "exec_command");
	if (pipe(data->fd_pipe) == -1)
		return ; // handle pipe error
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return ; // handle fork error
	if (data->pid[data->n_pid] == 0)
	{
		close(data->fd_pipe[READ_END]);
		dup2(data->fd_pipe[WRITE_END], STDOUT_FILENO); 
		close(data->fd_pipe[WRITE_END]);
		if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
			exit(data->last_exit_status); // check free
		if (get_cmd_with_path(data, cmd[0], &cmd_with_path) == FAILURE)
			exit(EXIT_FAILURE); // check free
		dprintf(2, "\e[34mcmd_with_path: %s\n\e[0m", cmd_with_path); //
		execve(cmd_with_path, cmd, data->env_msh);
		free(cmd_with_path);
		print_error_cmd(cmd[0]);
		exit(127); //send exit error status 
	}
	else if (data->pid[data->n_pid] > 0)
	{
		close(STDIN_FILENO);
		close(data->fd_pipe[WRITE_END]);
		dprintf(2, "\e[31mdup2\n\e[0m");
		dup2(data->fd_pipe[READ_END], STDIN_FILENO);
		close(data->fd_pipe[READ_END]);
		data->n_pid++;
	}
}

void	exec_nopipe_command(t_minishell *data, char **cmd, int end_index)
{

	char	*cmd_with_path;

	dprintf(2, "\nexec_nopipe_command current last, data->args[%d]: %s\n", end_index, data->args[end_index]); //
	if (is_env_changing_builtin(cmd, data) == TRUE)
		return ; // handle?

	data->executed_command = TRUE;
	print_array(cmd, "exec_command");
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return ; // handle fork error
	if (data->pid[data->n_pid] == 0)
	{
		if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
			exit(data->last_exit_status); // check free
		if (get_cmd_with_path(data, cmd[0], &cmd_with_path) == FAILURE)
			exit(EXIT_FAILURE); // check free
		dprintf(2, "\e[34mcmd_with_path: %s\n\e[0m", cmd_with_path); //
		execve(cmd_with_path, cmd, data->env_msh);
		free(cmd_with_path);
		print_error_cmd(cmd[0]);
		exit(127); //send exit error status 
	}
	else if (data->pid[data->n_pid] > 0)
		data->n_pid++;
}
