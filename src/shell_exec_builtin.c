/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:04:16 by demre             #+#    #+#             */
/*   Updated: 2024/03/18 17:26:06 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute cmd if it is a builtin command
 * @param cmd command with its parameters
 * @return SUCCESS if cmd correctly executed, FAILURE otherwise
 */

static int	is_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (SUCCESS);
	else if (!ft_strcmp(args[0], "pwd"))
		return (SUCCESS);
	else if (!ft_strcmp(args[0], "cd"))
		return (SUCCESS);
	else if (!ft_strcmp(args[0], "export"))
		return (SUCCESS);
	else if (!ft_strcmp(args[0], "env"))
		return (SUCCESS);
	else
		return (FAILURE);
}

int	exec_cmd_if_builtin(char **args, t_minishell *data)
{
	if (is_builtin(args) == SUCCESS)
	{
		if (!ft_strcmp(args[0], "echo"))
			builtin_echo(&(args[0]));
		else if (!ft_strcmp(args[0], "pwd"))
			builtin_pwd();
		else if (!ft_strcmp(args[0], "cd"))
		{
			builtin_cd(args[1], data);
			data->cd_to_execute = TRUE;//Doese not send data to father => send a message to father to execute cd ?
		}
		else if (!ft_strcmp(args[0], "export"))
			builtin_export(data->args);
		else if (!ft_strcmp(args[0], "env"))
			builtin_env();
		return (SUCCESS);
	}
	else
		return (FAILURE);
}
