/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:34:57 by blarger           #+#    #+#             */
/*   Updated: 2024/04/09 15:27:01 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_exported_variable(t_minishell *data)
{
	int	i;

	i = 0;
	while (data->env_msh[i])
	{
		printf("declare -x %s\n", data->env_msh[i]);
		i++;
	}
}

static int	is_valid_shell_var(char *arg, t_minishell *data)
{
	int	i;

	i = 0;
	dprintf(2, "is_valid_shell_var arg: %s\n", arg); //
	while (arg[i] && is_valid_ev_character(arg[i]) == TRUE)
		i++;
	if (i != 0 && ((arg[i] && arg[i] == '=')
		|| (arg[i] && arg[i] == '+' && arg[i + 1] && arg[i + 1] == '=')))
	{
		if (arg[i] == '+')
			i++;
		i++;
		while (arg[i] && is_valid_ev_character(arg[i]) == TRUE)
			i++;
		if (arg[i] == '\0')
		{
			dprintf(2, "IS VALID\n"); //
			return (TRUE);
		}
	}
	dprintf(2, "IS not VALID, last_exit_status set to 1\n"); //
	print_error_message_and_arg(IDENTIFIER, arg);
	data->last_exit_status = 1;
	return (FALSE);
	/* else if (arg[i] && is_valid_ev_character(arg[i]) == FALSE)
	{
		dprintf(2, "IS not VALID, last_exit_status set to 1\n"); //
		print_error_message_and_arg(IDENTIFIER, arg);
		data->last_exit_status = 1;
		return (FALSE);
	}
	else
	{
		dprintf(2, "IS not VALID\n"); //
		return (FALSE);
	} */
}

static int	does_env_var_exist(char **env_msh, char *new_var, int end)
{
	int	i;

	i = 0;
	while (env_msh[i])
	{
		if (ft_memcmp(env_msh[i], new_var, end) == 0
				&& env_msh[i][end] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static int	handle_shell_var(char ***env_msh, char *new_var)
{
	int	i;
	int	already_exists;
	int	result;

	i = 0;
	already_exists = FALSE;
	while (new_var[i] && is_valid_ev_character(new_var[i]) == TRUE)
		i++;
	already_exists = does_env_var_exist(*env_msh, new_var, i);
	result = FAILURE;
	if (new_var[i] && new_var[i] == '=' && already_exists == FALSE)
		result = new_shell_var(env_msh, new_var);
	else if (new_var[i] && new_var[i] == '=' && already_exists == TRUE)
		result = replace_shell_var(env_msh, new_var, i);
	else if (new_var[i] && new_var[i] == '+'
		&& new_var[i + 1] && new_var[i + 1] == '=' && already_exists == FALSE)
		result = new_shell_var_without_plus(env_msh, new_var, i);
	else if (new_var[i] && new_var[i] == '+'
		&& new_var[i + 1] && new_var[i + 1] == '=' && already_exists == TRUE)
		result = append_shell_var(env_msh, new_var, i);
	if (result == FAILURE || !(*env_msh))
		return (FAILURE);
	return (SUCCESS);
}

void	builtin_export(char **args, t_minishell *data)
{
	int	i;

	i = 1;
	if (!args[1])
		return (display_exported_variable(data));
	else if (command_with_pipe(data->args) == TRUE)
		return ;
	else
	{
		while (args[i])
		{
			if (is_valid_shell_var(args[i], data) == TRUE)
			{
				if (handle_shell_var(&data->env_msh, args[i]) == FAILURE)
				{
					data->last_exit_status = 1;
					print_error(MALLOC_FAIL);
				}
			}
			i++;
		}
	}
}
