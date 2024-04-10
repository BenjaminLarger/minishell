/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_cmd_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 14:16:49 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_parent_exec_command_with_pipe(t_minishell *data)
{
	close(data->fd_pipe[WRITE_END]);
	dup2(data->fd_pipe[READ_END], STDIN_FILENO);
	close(data->fd_pipe[READ_END]);
	if (data->file.has_outfile == TRUE)
	{
		dup2(data->original_stdout_fd, STDOUT_FILENO);
		close(data->original_stdout_fd);
		data->original_stdout_fd = dup(STDOUT_FILENO);
	}
	data->n_pid++;
}

static void	execute_or_fail(t_minishell *data, char **cmd)
{
	char	*cmd_with_path;

	if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
		exit(data->last_exit_status);
	if (get_cmd_with_path(data, cmd[0], &cmd_with_path) == FAILURE)
		exit(EXIT_FAILURE);
	execve(cmd_with_path, cmd, data->env_msh);
	free(cmd_with_path);
	print_error_cmd(cmd[0]);
	exit(127);
}

void	exec_command_with_pipe(t_minishell *data, char **cmd)
{
	if (is_env_changing_builtin(cmd, data) == TRUE)
		data->no_output_builtin_executed = TRUE;
	if (pipe(data->fd_pipe) == -1)
		return (print_strerror_and_set_exit_status(data));
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (print_strerror_and_set_exit_status(data));
	if (data->pid[data->n_pid] == 0)
	{
		close(data->fd_pipe[READ_END]);
		if (data->file.has_outfile == FALSE)
			dup2(data->fd_pipe[WRITE_END], STDOUT_FILENO);
		close(data->fd_pipe[WRITE_END]);
		if (data->no_output_builtin_executed == FALSE)
			execute_or_fail(data, cmd);
		exit(EXIT_SUCCESS);
	}
	else if (data->pid[data->n_pid] > 0)
		handle_parent_exec_command_with_pipe(data);
}
