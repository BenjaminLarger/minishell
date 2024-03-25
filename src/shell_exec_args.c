/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/25 16:50:12 by demre            ###   ########.fr       */
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
				exec_command(data, cmd);
			free_string_array(cmd);
			write_to_outfile_if_needed(data);
		}
		dprintf(2, "exec_args exit status = %d\n", data->last_exit_status);
		i++;
	}
	if (data->executed_command == TRUE)
		write_fdin_to_fdout(data->fd_pipe1[READ_END], STDOUT_FILENO);
	return (SUCCESS);
}
