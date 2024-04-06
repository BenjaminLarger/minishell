/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:04:16 by demre             #+#    #+#             */
/*   Updated: 2024/04/06 15:57:01 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute cmd if it is a builtin command
 * @param cmd command with its parameters
 * @return SUCCESS if cmd correctly executed, FAILURE otherwise
 */

void	check_and_replace_last_exit_status_call(char **args, t_minishell *data)
{
	int	i;

	i = 0;
	while (args[i] && ft_strcmp("|", args[i]))
	{
		if (!(ft_strcmp(args[i], "$?")))
		{
			free(args[i]);
			args[i] = ft_calloc(sizeof(char), 4);
			if (!args[i])
				return ; //Hanlde malloc failure
			args[i] = ft_itoa(data->last_exit_status);
		}
		i++;
	}
}

static int	is_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (SUCCESS);
	else if (!ft_strcmp(args[0], "pwd"))
		return (SUCCESS);
	else if (!ft_strcmp(args[0], "export"))
		return (SUCCESS);
	else if (!ft_strcmp(args[0], "env"))
		return (SUCCESS);
	else if (!ft_strcmp(args[0], "exit"))
		return (SUCCESS);
	else
		return (FAILURE);
}

int	exec_cmd_if_builtin(char **args, t_minishell *data)
{
	if (is_builtin(args) == SUCCESS)
	{
		data->executed_command = FALSE;
		data->last_exit_status = 0;
		if (!ft_strcmp(args[0], "echo"))
			builtin_echo(&(args[0]));
		else if (!ft_strcmp(args[0], "pwd"))
			builtin_pwd(data);
		else if (!ft_strcmp(args[0], "env"))
			builtin_env(data);
//		else if (!ft_strcmp(args[0], "export"))
//			builtin_export(args, data);
//		else if (!ft_strcmp(args[0], "exit"))
//			builtin_exit(data);
//		dprintf(2, "HERE builtin\n");
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

int	is_env_changing_builtin(char **cmd, t_minishell *data)
{
	int	i;

	i = 0;
	check_and_replace_last_exit_status_call(cmd, data);
	if (!ft_strcmp(cmd[0], "cd"))
	{
		builtin_cd(cmd[1], data);
		return (TRUE);
	}
	else if (!ft_strcmp(cmd[0], "export") && cmd[1] != NULL)
	{
		builtin_export(cmd, data);
		return (TRUE);
	}
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		builtin_unset(cmd, data);
		return (TRUE);
	}
	else if (!ft_strcmp(cmd[0], "exit"))
	{
		builtin_exit(data, cmd);
		return (TRUE);
	}
	return (FALSE);
}
