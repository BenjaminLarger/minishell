/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/04/03 18:46:26 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_minishell *data, char **cmd, int end_index)
{
	char	*cmd_with_path;

	dprintf(2, "\ncurrent last, data->args[%d]: %s\n", end_index, data->args[end_index]); //
	if (is_env_changing_builtin(cmd, data) == TRUE)
		return ;
		
//	if (data->n_pid >= 1)
//	{
//	dprintf(2, "\e[31mClosing in exec_command data->fd_pipe[%d][READ_END]: %d\n\e[0m", data->n_pid - 1, data->fd_pipe[data->n_pid - 1][READ_END]);
//		close(data->fd_pipe[data->n_pid - 1][READ_END]);
//	}

	data->executed_command = TRUE;
	print_array(cmd, "exec_command");
	data->fd_pipe[data->n_pid] = (int *)malloc(2 * sizeof(int));
	if (!(data->fd_pipe[data->n_pid]))
		return ; // handle malloc error
	if (pipe(data->fd_pipe[data->n_pid]) == -1)
		return ; // handle pipe error
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return ; // handle fork error
	if (data->pid[data->n_pid] == 0)
	{
		close(data->fd_pipe[data->n_pid][READ_END]);
		dup2(data->fd_pipe[data->n_pid][WRITE_END], STDOUT_FILENO); 
		close(data->fd_pipe[data->n_pid][WRITE_END]);
		if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
		{
			exit(data->last_exit_status);
		}
		// SUCCESS, EXEC_FAIL (builtin exist, mais exec failed), NOT_BUILTIN
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
		close(data->fd_pipe[data->n_pid][WRITE_END]);
		dprintf(2, "\e[31mdup2\n\e[0m");
		dup2(data->fd_pipe[data->n_pid][READ_END], STDIN_FILENO);
		close(data->fd_pipe[data->n_pid][READ_END]);
		data->n_pid++;
		data->n_pipe++;
	}
}

void	exec_nopipe_command(t_minishell *data, char **cmd, int end_index)
{

	char	*cmd_with_path;

	dprintf(2, "\nexec_nopipe_command current last, data->args[%d]: %s\n", end_index, data->args[end_index]); //
	if (is_env_changing_builtin(cmd, data) == TRUE)
		return ;

	data->executed_command = TRUE;
	print_array(cmd, "exec_command");
	data->pid[data->n_pid] = fork();
	if (data->pid[data->n_pid] == -1)
		return ; // handle fork error
	if (data->pid[data->n_pid] == 0)
	{
		if (exec_cmd_if_builtin(cmd, data) == SUCCESS)
		{
			exit(data->last_exit_status);
		}
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
//		close(STDIN_FILENO);
//		dup2(data->original_stdin_fd, STDIN_FILENO);
		data->n_pid++;
	}
}
