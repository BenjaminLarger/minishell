/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 13:39:51 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command_with_pipe(t_minishell *data, char **cmd, int end_index)
{
	char	*cmd_with_path;

	dprintf(2, "\nexec_command_with_pipe current last, data->args[%d]: %s\n", end_index, data->args[end_index]); //
	if (is_env_changing_builtin(cmd, data) == TRUE)
		data->no_output_builtin_executed = TRUE;
	print_array(cmd, "exec_command");
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
		{
			if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
				exit(data->last_exit_status); // errors handled and all freed
			if (get_cmd_with_path(data, cmd[0], &cmd_with_path) == FAILURE)
				exit(EXIT_FAILURE); // errors handled and all freed
			dprintf(2, "\e[34mcmd_with_path: %s\n\e[0m", cmd_with_path); //
			execve(cmd_with_path, cmd, data->env_msh);
			free(cmd_with_path);
			print_error_cmd(cmd[0]);
			exit(127); //send exit error status 
		}
		exit(EXIT_SUCCESS);
	}
	else if (data->pid[data->n_pid] > 0)
	{
		close(data->fd_pipe[WRITE_END]);
		dprintf(2, "\e[31mdup2\n\e[0m");
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
}

void	exec_command_nopipe(t_minishell *data, char **cmd, int end_index)
{
	char	*cmd_with_path;

	dprintf(2, "\nexec_command_nopipe current last, data->args[%d]: %s\n", end_index, data->args[end_index]); //
	if (is_env_changing_builtin(cmd, data) == TRUE)
		return ; // handle?

	if (data->file.previous_had_outfile == TRUE)
	{
		data->file.temp_infile = open(".temp_infile", O_RDONLY | O_CREAT, 0644);
		dup2(data->file.temp_infile, STDIN_FILENO);
		close(data->file.temp_infile);
	}
	print_array(cmd, "exec_command");
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (print_strerror_and_set_exit_status(data));
	if (data->pid[data->n_pid] == 0)
	{
		if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
			exit(data->last_exit_status); // errors handled and all freed
		if (get_cmd_with_path(data, cmd[0], &cmd_with_path) == FAILURE)
			exit(EXIT_FAILURE); // errors handled and all freed
		dprintf(2, "\e[34mcmd_with_path: %s\n\e[0m", cmd_with_path); //
		execve(cmd_with_path, cmd, data->env_msh);
		free(cmd_with_path);
		print_error_cmd(cmd[0]);
		exit(127);
	}
	else if (data->pid[data->n_pid] > 0)
	{
		data->n_pid++;
		
		dup2(data->original_stdout_fd, STDOUT_FILENO);
		close(data->original_stdout_fd);
		dup2(data->original_stdin_fd, STDIN_FILENO);
		close(data->original_stdin_fd);
	}
}
