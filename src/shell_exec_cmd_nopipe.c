/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_cmd_nopipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 14:17:01 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_input_command_nopipe(t_minishell *data)
{
	if (data->file.previous_had_outfile == TRUE)
	{
		data->file.temp_infile = open(".temp_infile", O_RDONLY | O_CREAT, 0644);
		dup2(data->file.temp_infile, STDIN_FILENO);
		close(data->file.temp_infile);
	}
}

static void	handle_parent_exec_command_nopipe(t_minishell *data)
{
	data->n_pid++;
	dup2(data->original_stdout_fd, STDOUT_FILENO);
	close(data->original_stdout_fd);
	dup2(data->original_stdin_fd, STDIN_FILENO);
	close(data->original_stdin_fd);
}

void	exec_command_nopipe(t_minishell *data, char **cmd)
{
	char	*cmd_with_path;

	if (is_env_changing_builtin(cmd, data) == TRUE)
		return ;
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return (print_strerror_and_set_exit_status(data));
	if (data->pid[data->n_pid] == 0)
	{
		handle_child_input_command_nopipe(data);
		if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
			exit(data->last_exit_status);
		if (get_cmd_with_path(data, cmd[0], &cmd_with_path) == FAILURE)
			exit(EXIT_FAILURE);
		execve(cmd_with_path, cmd, data->env_msh);
		free(cmd_with_path);
		print_error_cmd(cmd[0]);
		exit(127);
	}
	else if (data->pid[data->n_pid] > 0)
		handle_parent_exec_command_nopipe(data);
}
