/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 19:00:38 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_args_init(t_minishell *data, int *i, int *start)
{
	*i = 0;
	*start = 0;
	data->original_stdin_fd = dup(STDIN_FILENO);
	data->original_stdout_fd = dup(STDOUT_FILENO);
	data->n_pid = 0;
	// add realloc
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
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		getcwd(data->last_valid_dir, sizeof(data->last_valid_dir));
	dup2(data->original_stdout_fd, STDOUT_FILENO);
	close(data->original_stdout_fd);
	dup2(data->original_stdin_fd, STDIN_FILENO);
	close(data->original_stdin_fd);
	free(data->pid);
	free(data->status);
	if (access(".temp_infile", F_OK | R_OK) == 0)
		unlink(".temp_infile");
}

static void	reset(t_minishell *data, int *start_index, int i)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		export_pwd_or_old_pwd(data, cwd, "PWD=");
	*start_index = i;
	data->no_output_builtin_executed = FALSE;
	data->file.previous_had_outfile = FALSE;
	if (data->file.has_outfile == TRUE)
	{
		data->file.has_outfile = FALSE;
		data->file.previous_had_outfile = TRUE;
	}
	data->file.has_infile = FALSE;
	data->file.has_heredoc = FALSE;
}

static void	wait_for_child_processes(t_minishell *data)
{
	int		i;

	i = 0;
	while (i < data->n_pid)
	{
		waitpid(data->pid[i], &data->status[i], 0);
		data->last_exit_status = WEXITSTATUS(data->status[i]);
		i++;
	}
	exec_args_cleanup(data);
}

int	exec_args(t_minishell *data)
{
	int		i;
	int		start;
	char	**cmd;

	if (exec_args_init(data, &i, &start) == FAILURE)
		return (print_strerror_and_set_exit_status_and_failure(data));
	while (i < data->n_args && data->args[i])
	{
		reset(data, &start, i);
		while (data->args[i] && ft_strcmp(data->args[i], "|") != 0)
			i++;
		if (handle_redirections(data, data->args, start, i) == SUCCESS)
		{
			if (get_cmd_without_redirections(data, &cmd, start, i) == FAILURE)
				return (FAILURE);
			if (cmd && *cmd && data->args[i] && !ft_strcmp(data->args[i], "|"))
				exec_command_with_pipe(data, cmd);
			else if (cmd && *cmd && !data->args[i])
				exec_command_nopipe(data, cmd);
			free_string_array(cmd);
		}
		i++;
	}
	wait_for_child_processes(data);
	return (SUCCESS);
}
