/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:44:40 by demre             #+#    #+#             */
/*   Updated: 2024/03/20 18:46:33 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_args_loop(t_minishell *data);

/* IMPORTANT
After using dup2, STDIN refers to the read end of the pipe,
not the actual standard input.
When we try to call readline, it tries to perform an operation
on this new stdin.
This operation is not supported, leading to an error !!!
To solve this issue, we can save the initial file descriptor
using : data->save_stdin_fd = dup(STDIN_FILENO);

The dup() function returns a new file descriptor having the following
in common with the original open file descriptor fildes:
	same open file (or pipe)
	same file pointer (that is, both file descriptors share one file pointer)
	same access mode (read, write or read/write).

Once the while loop has processed pipes and dup operations, we can restore the
original STDIN.
 */

int	execute_command(t_minishell *data, int i)
{
	if (!ft_strcmp(data->args[i], "echo"))
		builtin_echo(&(data->args[i]));
	else if (!ft_strcmp(data->args[i], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(data->args[i], "cd"))
		builtin_cd(data->args[i], data);
	else if (!ft_strcmp(data->args[i], "export"))
		builtin_export(data->args, data);
	else if (!ft_strcmp(data->args[i], "env"))
	{
		builtin_env();
		return (i + 1);
	}
	//else
		//simple_command(&(data->args[i]), data, envp);
	return count_commands(&(data->args[i]));
	/* else
		execve() */
}

static void	process_args_loop(t_minishell *data) //Should we process args one by one or pipe per pipe
{
	int	i;

	i = 0;
	while (data->args[i])
	{
		if (is_linker(data->args[i]) == TRUE)
			i += handle_redirection(&(data->args[i]), data);
		else //it is a simple command
			i += execute_command(data, i);
		printf("i = %d\n\n", i);
	}
}

int	process_args(t_minishell *data)
{
	//split_args_into_cmds(data);
	//print_all_cmds_and_linkers(data);
	data->save_stdin_fd = dup(STDIN_FILENO);
	handle_last_exit_status_cmd(data->args, data);
	handle_env_variable(data->args);
	process_args_loop(data);
	dup2(data->save_stdin_fd, STDIN_FILENO);
	close(data->save_stdin_fd);
	if (data->file.in_fd)
		close(data->file.in_fd);
	if (data->file.out_fd)
		close(data->file.out_fd);
/* 	else if (!ft_strcmp(data->args[1], "<<", 2))
		process_here_file(data, 2); */
	return (SUCCESS);
}
