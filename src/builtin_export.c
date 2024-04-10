/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:34:57 by blarger           #+#    #+#             */
/*   Updated: 2024/04/10 14:13:34 by blarger          ###   ########.fr       */
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
	if (arg[i] && ft_isdigit(arg[i]))
	{
		print_error_message_and_arg(IDENTIFIER, arg);
		return (return_true_or_false_set_exit_status(FALSE, 1, data));
	}
	while (arg[i] && is_valid_ev_character(arg[i]) == TRUE)
		i++;
	if (i != 0 && ((arg[i] && arg[i] == '=')
			|| (arg[i] && arg[i] == '+' && arg[i + 1] && arg[i + 1] == '=')))
	{
		return (return_true_or_false_set_exit_status(TRUE, 0, data));
	}
	else if (arg[i] && is_valid_ev_character(arg[i]) == FALSE)
	{
		print_error_message_and_arg(IDENTIFIER, arg);
		return (return_true_or_false_set_exit_status(FALSE, 1, data));
	}
	else
		return (return_true_or_false_set_exit_status(FALSE, 1, data));
}

static int	does_env_var_exist(char **env_msh, char *new_var, int end)
{
	int	i;

	i = 0;
	while (env_msh[i])
	{
		if (ft_memcmp(env_msh[i], new_var, end) == 0 && env_msh[i][end] == '=')
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
			if (is_valid_shell_var(args[i], data) == TRUE
				&& is_valid_shell_value(args[i], data) == TRUE)
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
