/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_get_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/04/09 17:11:22 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_number_of_command_arguments(t_minishell *data,
	int start, int end, int *cmd_args_count)
{
	int	i;

	i = start;
	*cmd_args_count = 0;
	while (i < end && data->args[i])
	{
		if (!is_linker(data->args[i]))
			(*cmd_args_count)++;
		else if (is_linker(data->args[i]))
			i++;
		i++;
	}
}

static int	assign_command_arguments(t_minishell *data, char ***cmd,
	int arg_index, int cmd_args_count)
{
	int	cmd_index;

	*cmd = (char **)malloc((cmd_args_count + 1) * sizeof(char *));
	if (!(*cmd))
		return (FAILURE);
	cmd_index = 0;
	while (cmd_index < cmd_args_count)
	{
		if (!is_linker(data->args[arg_index]))
		{
			(*cmd)[cmd_index] = ft_strdup(data->args[arg_index]);
			if (!(*cmd))
			{
				free_n_string_array(*cmd, cmd_index);
				return (FAILURE);
			}
			cmd_index++;
		}
		else if (is_linker(data->args[arg_index]))
			arg_index++;
		arg_index++;
	}
	(*cmd)[cmd_index] = NULL;
	return (SUCCESS);
}

/**
 * @brief Assign the command and its parameters to cmd array by removing 
 * redirection indicators and the associated filenames from command group 
 * (until next pipe or end-of-line). 
 */
int	get_cmd_without_redirections(t_minishell *data, char ***cmd,
	int start, int end)
{
	int	cmd_args_count;

	count_number_of_command_arguments(data, start, end, &cmd_args_count);
	dprintf(2, "get_cmd: start %d, end %d, *cmd_args_count %d\n", start, end, cmd_args_count); //
	if (assign_command_arguments(data, cmd, start, cmd_args_count) == FAILURE)
		return (print_strerror_and_set_exit_status_and_failure(data));
	return (SUCCESS);
}
