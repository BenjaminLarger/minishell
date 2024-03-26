/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/26 14:23:33 by demre            ###   ########.fr       */
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
		write_fdin_to_fdout(data->fd_pipe1[READ_END], data->file.out_fd);
		close(data->file.out_fd);
	}
}

int	exec_args(t_minishell *data)
{
	int		i;
	int		start_index;
	char	**cmd;

	int			*pid;
	int			*status;
	int			n_pid;
	
	n_pid = 0;
	pid = (int *)malloc(1000 * sizeof(int));
	status = (int *)malloc(1000 * sizeof(int));
	if (!pid || !status)
		return (FAILURE); // malloc failure

	i = 0;
	start_index = 0;
	print_array(data->args); //
	while (i < data->n_args && data->args[i])
	{
		reset(data, &start_index, i);
		while (data->args[i] && ft_strcmp(data->args[i], "|"))
			i++;
		dprintf(2, "\nPipe or eof at i = %d\n", i); //
		if (handle_redirections_until_next_pipe(data, data->args, start_index, i) == SUCCESS)
		{
			if (get_cmd_without_redirections(data, &cmd, start_index, i) == FAILURE)
				return (FAILURE); // malloc failure
			if (cmd && *cmd)
				exec_command(data, cmd, &pid, &n_pid);
			free_string_array(cmd);
			write_to_outfile_if_needed(data);
		}
		dprintf(2, "exec_args exit status = %d\n", data->last_exit_status);
		i++;
	}
	// Moved waitpid out of the loop so every execution is starting at the same time
	i = 0;
	while (i < n_pid)
	{
		waitpid(pid[i], &status[i], 0);
		dprintf(2, "done waiting for child pid[%d]: %d\n", i, pid[i]);
		if (WIFEXITED(status[i]))
		{
			if (WEXITSTATUS(status[i]) != 0)
			{
				dprintf(2, "errno exit status in first child = %d\n", (WEXITSTATUS(status[i])));
				data->last_exit_status = WEXITSTATUS(status[i]);
				//data->last_exit_status = 127;
			}
		}
		dprintf(2, "errno exit status in first child = %d\n", (WEXITSTATUS(status[i])));
		i++;
	}
	free(pid);
	free(status);
	if (data->executed_command == TRUE)
		write_fdin_to_fdout(data->fd_pipe1[READ_END], STDOUT_FILENO);
	return (SUCCESS);
}
