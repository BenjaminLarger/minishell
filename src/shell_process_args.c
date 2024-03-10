/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:44:40 by demre             #+#    #+#             */
/*   Updated: 2024/03/10 10:09:09 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_args(t_minishell *data)
{
//	if (split_args_into_cmds(data) == FAILURE)
//		return (FAILURE);
//	if (data->n_args == 0)
//		return (SUCCESS);
	handle_env_variable(data->args);
	if (!ft_strncmp(data->args[0], "echo", 4) && data->args[0][4] == '\0')
		builtin_echo(data->args, data->n_cmds);
	else if (!ft_strncmp(data->args[0], "pwd", 3) && data->args[0][3] == '\0')
		builtin_pwd();
	else if (!ft_strncmp(data->args[0], "cd", 2) && data->args[0][2] == '\0')
		builtin_cd(data->args[1], data);
	else if (!ft_strncmp(data->args[0], "export", 6) && data->args[0][6] == '\0')
		builtin_export(data->args);
	else if (!ft_strncmp(data->args[0], "env", 3) && data->args[0][3] == '\0')
		builtin_env();
/* 	else if (!ft_strncmp(data->args[1], "<<", 2))
		process_here_file(data, 2); */
	return (SUCCESS);
}
