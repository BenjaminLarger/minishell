/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:44:40 by demre             #+#    #+#             */
/*   Updated: 2024/03/12 12:40:39 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_args_loop(t_minishell *data);

int	process_args(t_minishell *data)
{
	//split_args_into_cmds(data);
	//print_all_cmds_and_linkers(data);
	handle_last_exit_status_cmd(data->args);
	handle_env_variable(data->args);
	process_args_loop(data);
	if (data->file.in_fd)
		close(data->file.in_fd);
	if (data->file.out_fd)
		close(data->file.out_fd);
/* 	else if (!ft_strcmp(data->args[1], "<<", 2))
		process_here_file(data, 2); */
	return (SUCCESS);
}

static void	process_args_loop(t_minishell *data) //Should we process args one by one or pipe per pipe
{
	int	i;

	i = 0;
	while (data->args[i])
	{
		//create_fork(data);
		//if is child => write in write-end pipe {
		if (is_linker(data->args[i]) == TRUE)
			i += handle_redirection(&(data->args[i]), data);
		else //it is a simple command
			i += execute_command(data, i);
		//}
		//else => read read-end pipe
		printf("i = %d\n\n", i);
	}
}

int	execute_command(t_minishell *data, int i)
{
	if (!ft_strcmp(data->args[i], "echo"))
		builtin_echo(&(data->args[i]));
	else if (!ft_strcmp(data->args[i], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(data->args[i], "cd"))
		builtin_cd(data->args[i], data);
	else if (!ft_strcmp(data->args[i], "export"))
		builtin_export(data->args);
	else if (!ft_strcmp(data->args[i], "env"))
		builtin_env();
	return count_arg_after_cmd(&(data->args[i]));
	/* else
		execve() */
}

