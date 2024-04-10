/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:04:16 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 17:12:37 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_and_replace_last_exit_status_call(char **args,
		t_minishell *data)
{
	int	i;

	i = 0;
	while (args[i] && ft_strcmp("|", args[i]))
	{
		if (!(ft_strcmp(args[i], "$?")))
		{
			free(args[i]);
			args[i] = ft_itoa(data->last_exit_status);
			if (!args[i])
				return (print_strerror_and_set_exit_status(data));
		}
		i++;
	}
	data->last_exit_status = 0;
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
		data->last_exit_status = 0;
		if (!ft_strcmp(args[0], "echo"))
			builtin_echo(&(args[0]));
		else if (!ft_strcmp(args[0], "pwd"))
			builtin_pwd(data);
		else if (!ft_strcmp(args[0], "env"))
			builtin_env(data);
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
