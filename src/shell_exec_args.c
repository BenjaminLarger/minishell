/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 19:54:37 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	get_cmd_and_execute(t_minishell *data, int start, int i)
{
	char	**cmd;

	if (get_cmd_without_redirections(data, &cmd, start, i) == FAILURE)
		return (FAILURE);
	if (cmd && !(*cmd) && (data->file.has_heredoc == TRUE
			|| data->file.has_infile == TRUE))
	{
		data->file.in_fd = open(".temp_infile", O_RDONLY | O_CREAT, 0644);
		dup2(data->file.in_fd, STDIN_FILENO);
		close(data->file.in_fd);
	}
	if (cmd && !(*cmd) && data->file.has_outfile == TRUE)
	{
		dup2(data->original_stdout_fd, STDOUT_FILENO);
		close(data->original_stdout_fd);
		data->original_stdout_fd = dup(STDOUT_FILENO);
	}
	if (cmd && *cmd && data->args[i] && !ft_strcmp(data->args[i], "|"))
		exec_command_with_pipe(data, cmd);
	else if (cmd && *cmd && !data->args[i])
		exec_command_nopipe(data, cmd);
	free_string_array(cmd);
	return (SUCCESS);
}

int	exec_args(t_minishell *data)
{
	int		i;
	int		start;

	if (exec_args_init(data, &i, &start) == FAILURE)
		return (print_strerror_and_set_exit_status_and_failure(data));
	while (i < data->n_args && data->args[i])
	{
		reset(data, &start, i);
		while (data->args[i] && ft_strcmp(data->args[i], "|") != 0)
			i++;
		if (handle_redirections(data, data->args, start, i) == SUCCESS)
		{
			if (get_cmd_and_execute(data, start, i) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	wait_for_child_processes(data);
	exec_args_cleanup(data);
	return (SUCCESS);
}
