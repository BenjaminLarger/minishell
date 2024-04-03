/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/04/03 21:08:49 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_args_init(t_minishell *data, int *i, int *start)
{
	*i = 0;
	*start = 0;
	data->original_stdin_fd = open("/dev/tty", O_RDONLY);
	data->original_stdout_fd = dup(STDOUT_FILENO);
	data->n_pid = 0;
	data->pid = (int *)malloc(1000 * sizeof(int));
	if (!data->pid)
		return (FAILURE);
	data->status = (int *)malloc(1000 * sizeof(int));
	if (!data->status)
		return (FAILURE);
	return (SUCCESS);
}

static void	exec_args_cleanup(t_minishell *data)
{
	dup2(data->original_stdout_fd, STDOUT_FILENO);
	close(data->original_stdout_fd);
	dup2(data->original_stdin_fd, STDIN_FILENO);
	close(data->original_stdin_fd);
	free(data->pid);
	free(data->status);
}

static void	reset(t_minishell *data, int *start_index, int i)
{
	*start_index = i;
	data->file.has_infile = FALSE;
	data->file.has_outfile = FALSE;
	data->file.has_heredoc = FALSE;
	data->executed_command = FALSE; // executed_command not required anymore?
}

static void	wait_for_child_processes(t_minishell *data)
{
	int		i;

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
}

int	exec_args(t_minishell *data)
{
	int		i;
	int		start;
	char	**cmd;

	if (exec_args_init(data, &i, &start) == FAILURE)
		return (FAILURE); // malloc failure
print_array(data->args, "exec_args"); //
	while (i < data->n_args && data->args[i])
	{
		reset(data, &start, i);
		while (data->args[i] && ft_strcmp(data->args[i], "|") != 0)
			i++;
		dprintf(2, "\nPipe or eof at i = %d. data->args[i]: %s\n", i, data->args[i]); //
		if (handle_redirections(data, data->args, start, i) == SUCCESS)
		{
			if (get_cmd_without_redirections(data, &cmd, start, i) == FAILURE)
				return (FAILURE); // malloc failure
			if (cmd && *cmd && data->args[i] && !ft_strcmp(data->args[i], "|"))
				exec_command(data, cmd, i);
			else if (cmd && *cmd && !data->args[i])
				exec_nopipe_command(data, cmd, i);
			free_string_array(cmd);
		}
//		else
//			break ; // ?
		dprintf(2, "exec_args exit status = %d\n", data->last_exit_status);
		i++;
	}
	wait_for_child_processes(data);
	exec_args_cleanup(data);
//	check_open_fd("end of exec_args");
//	print_pipes_fd(data);
	return (SUCCESS);
}
