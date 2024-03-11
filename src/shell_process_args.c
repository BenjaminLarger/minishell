/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:44:40 by demre             #+#    #+#             */
/*   Updated: 2024/03/11 17:07:23 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_args_loop(t_minishell *data);

int	process_args(t_minishell *data)
{
//	if (split_args_into_cmds(data) == FAILURE)
//		return (FAILURE);
//	if (data->n_args == 0)
//		return (SUCCESS);
	split_args_into_cmds(data);
	//print_all_cmds_and_linkers(data);
	handle_last_exit_status_cmd(data->args);
	handle_env_variable(data->args);
	process_args_loop(data);
/* 	else if (!ft_strcmp(data->args[1], "<<", 2))
		process_here_file(data, 2); */
	return (SUCCESS);
}

static void	process_args_loop(t_minishell *data) //Should we process args one by one or pipe per pipe
{
	int	i;

	i = 0;
	while (i <= count_pipes(data))
	{
		//create_fork(data);
		//if is child => write in write-end pipe {
		if (is_linker(data->args[i]) == TRUE)
			handle_redirection(&data->args[i]);
		else //it is a simple command
			execute_command(data, i);
		//}
		//else => read read-end pipe
		i = get_next_pipe(&(data->args[i])); //Here get the array from i element
	}
}

void	execute_command(t_minishell *data, int i)
{
	if (!ft_strcmp(data->args[i], "echo"))
		builtin_echo(data->args);
	else if (!ft_strcmp(data->args[i], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(data->args[i], "cd"))
		builtin_cd(data->args[1], data);
	else if (!ft_strcmp(data->args[i], "export"))
		builtin_export(data->args);
	else if (!ft_strcmp(data->args[i], "env"))
		builtin_env();
	/* else
		execve() */
}

