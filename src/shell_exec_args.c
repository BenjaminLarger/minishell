/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/27 18:35:41 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset(t_minishell *data, int *start_index, int i)
{
	*start_index = i;
	data->file.has_infile = FALSE;
	data->file.has_outfile = FALSE;
	data->file.has_heredoc = FALSE;
	data->executed_command = FALSE;
}

/**
 * @brief Write to output file if this command group has an output redirection.
 */
static void	write_to_outfile_if_needed(t_minishell *data)
{
	if (data->file.has_outfile == TRUE)
	{
//		check if [data->n_pid - 1]
		write_fdin_to_fdout(data->fd_pipe[data->n_pid - 1][READ_END], data->file.out_fd);
		close(data->fd_pipe[data->n_pid - 1][READ_END]);
		close(data->file.out_fd);
	}
}

int	exec_args(t_minishell *data)
{
	int		i;
	int		start_index;
	char	**cmd;
	
	data->n_pid = 0;
	data->pid = (int *)malloc(1000 * sizeof(int));
	data->status = (int *)malloc(1000 * sizeof(int));
	data->fd_pipe = (int **)malloc(1000 * sizeof(int *));
	if (!data->pid || !data->status || !data->fd_pipe)
		return (FAILURE); // malloc failure

	i = 0;
	start_index = 0;
	print_array(data->args, "exec_args"); //
	while (i < data->n_args && data->args[i])
	{
		reset(data, &start_index, i);
		while (data->args[i] && ft_strcmp(data->args[i], "|")) //!= 0
			i++;
		dprintf(2, "\nPipe or eof at i = %d. data->args[i]: %s\n", i, data->args[i]); //
		if (handle_redirections_until_next_pipe(data, data->args, start_index, i) == SUCCESS)
		{
			if (get_cmd_without_redirections(data, &cmd, start_index, i) == FAILURE)
				return (FAILURE); // malloc failure
			if (cmd && *cmd)
				exec_command(data, cmd, i);
			free_string_array(cmd);
			write_to_outfile_if_needed(data);
		}
		dprintf(2, "exec_args exit status = %d\n", data->last_exit_status);
		i++;
	}
	// Moved waitpid out of the loop so every execution is starting at the same time
	i = 0;
	while (i < data->n_pid)
	{
		waitpid(data->pid[i], &data->status[i], 0);
		dprintf(2, "done waiting for child pid[%d]: %d\n", i, data->pid[i]);
		if (WIFEXITED(data->status[i]))
		{
			if (WEXITSTATUS(data->status[i]) != 0)
			{
				dprintf(2, "errno exit status in first child = %d\n", (WEXITSTATUS(data->status[i])));
				data->last_exit_status = WEXITSTATUS(data->status[i]);
				//data->last_exit_status = 127;
			}
		}
		dprintf(2, "errno exit status in first child = %d\n", (WEXITSTATUS(data->status[i])));
		i++;
	}
	if (data->executed_command == TRUE)
	{
		write_fdin_to_fdout(data->fd_pipe[data->n_pid - 1][READ_END], STDOUT_FILENO);
		dprintf(2, "\e[31mClosing in exec_args data->fd_pipe[%d][READ_END]: %d\n\e[0m", data->n_pid - 1, data->fd_pipe[data->n_pid - 1][READ_END]);
		close(data->fd_pipe[data->n_pid - 1][READ_END]);
	}

//	check_open_fd("end of exec_args");
//	print_pipes_fd(data);
	
	free(data->pid);
	free(data->status);
	free_int_array(data->fd_pipe, data->n_pid);
	return (SUCCESS);
}
