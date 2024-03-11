/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:00:30 by demre             #+#    #+#             */
/*   Updated: 2024/03/11 15:25:00 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmds_groups(t_minishell *data)
{
	int		i;
	int		linker_index;
	int		cmd_start_index;

	data->n_cmds = 0;
	data->n_linker = 0;
	linker_index = -10;
	cmd_start_index = 0;
	i = 0;
	while (data->args[i])
	{
		if (is_linker(data->args[i]))
		{
//			if (i == linker_index + 1)
//				return (FAILURE);
			linker_index = i;
			data->n_linker++;
			if (cmd_start_index < i)
				data->n_cmds++;
			if (data->args[i + 1])
				cmd_start_index = i + 1;
		}
		i++;
	}
	if (linker_index != i - 1)
		data->n_cmds++;
	return (SUCCESS);
}

static int	count_cmds_group_parameters(t_minishell *data)
{
	int		i;
	int		j;
	int		linker_index;
	int		cmd_start_index;

	linker_index = -10;
	cmd_start_index = 0;
	i = 0;
	j = 0;
	while (data->args[i])
	{
		if (is_linker(data->args[i]))
		{
			linker_index = i;
			if (cmd_start_index < i)
				data->cmds[j++].n_cmd_args = linker_index - cmd_start_index;
			if (data->args[i + 1])
				cmd_start_index = i + 1;
		}
		i++;
	}
	if (linker_index != i - 1)
		data->cmds[j].n_cmd_args = i - cmd_start_index;
	return (SUCCESS);
}

static void	assign_cmds_groups(t_minishell *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (data->args[i])
	{
		if (!is_linker(data->args[i]))
			data->cmds[j].cmd[k++] = data->args[i];
		else
		{
			data->cmds[j].cmd[k] = NULL;
			data->linker[j++] = data->args[i];
			k = 0;
		}
		i++;
	}
	if (data->n_args == 0 || !is_linker(data->args[i - 1]))
		data->cmds[j].cmd[k] = NULL;
	data->linker[j] = NULL;
}

/**
 * @brief Split the args array into groups of commands
 * @param t_minishell Structure representing the shared data and parameters.
 * @return 
 */
int		split_args_into_cmds(t_minishell *data)
{
	int	j;
	
	if (count_cmds_groups(data) == FAILURE)
	{
		perror("minish syntax error, two consecutive linker");
		return (FAILURE);
	}
	if (data->n_linker > 0 && data->n_cmds == 0)
	{
		perror("minish syntax error, prompt is only one linker");
		return (FAILURE);
	}
	if (data->n_args == 0)
		return (SUCCESS);
	data->cmds = (t_cmd *)malloc((data->n_cmds + 1) * sizeof(t_cmd));
	if (!data->cmds)
		return (FAILURE);
	data->linker = (char **)malloc((data->n_linker + 1) * sizeof(char *));
	if (!data->linker)
		return (FAILURE);
	count_cmds_group_parameters(data);
	j = 0;
	while (j < data->n_cmds)
	{
		data->cmds[j].cmd
					= malloc((data->cmds[j].n_cmd_args + 1) * sizeof(char *));
		if (!data->cmds[j].cmd)
		{
			// free on malloc failure
			return (FAILURE);
		}
		j++;
	}
	if (data->args)
		assign_cmds_groups(data);

	print_all_cmds_and_linkers(data);
	return (SUCCESS);
}
