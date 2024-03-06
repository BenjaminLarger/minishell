/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:44:40 by demre             #+#    #+#             */
/*   Updated: 2024/03/06 12:51:04 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_args(t_minishell *data)
{
//	if (split_args_into_cmds(data) == FAILURE)
//		return (FAILURE);

	if (!ft_strncmp(data->args[0], "echo", 4))
		builtin_echo(data->args, 3); //replace 4 by n_cmds
	else if (!ft_strncmp(data->args[0], "pwd", 3))
		builtin_pwd(); // change to n cmds
	else if (!ft_strncmp(data->args[0], "cd", 2))
		builtin_cd(data->args[1]);
/* 	else if (!ft_strncmp(data->args[1], "<<", 2))
		process_here_file(data, 2); */
	return (SUCCESS);
}
