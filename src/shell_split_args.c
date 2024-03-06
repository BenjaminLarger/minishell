/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:00:30 by demre             #+#    #+#             */
/*   Updated: 2024/03/06 16:27:16 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_linker(char *str)
{
	if (ft_strcmp(str, "|") == 0
		|| ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0
	)
		return (TRUE);
	return (FALSE);
}

static int	count_cmds_groups(t_minishell *data)
{
	int		i;
	int		next_linker_index;
	int		cmd_start_index;

	data->n_cmds = 0;
	data->n_linker = 0;
	next_linker_index = -10;
	cmd_start_index = 0;
	i = 0;
	while (data->args[i])
	{
		if (is_linker(data->args[i]))
		{
			if (i == next_linker_index + 1)
			{
				perror("minish syntax error");
				return (FAILURE);
			}
			next_linker_index = i;
			data->n_linker++;
			if (cmd_start_index < i)
				data->n_cmds++;
			if (data->args[i + 1])
				cmd_start_index = i + 1;
		}
		i++;
	}
	if (next_linker_index != i - 1)
		data->n_cmds++;
	return (SUCCESS);
}
/*
	ls -l | tr " " g
	cmds[0].cmd[0] = "ls",		n_cmds = 1, n_linker = 0
	cmds[0].cmd[1] = "-l",		n_cmds = 1, n_linker = 0
	linker[0] = "|",			n_cmds = 1, n_linker = 1
	cmds[1].cmd[0] = "tr",		n_cmds = 2, n_linker = 1
	cmds[1].cmd[1] = "" "",		n_cmds = 2, n_linker = 1
	cmds[1].cmd[2] = "g",		n_cmds = 2, n_linker = 1

	grep i < infile
	cmds[0].cmd[0] = "grep",	n_cmds = 1, n_linker = 0
	cmds[0].cmd[1] = "i",		n_cmds = 1, n_linker = 0
	linker[0] = "<",			n_cmds = 1, n_linker = 1
	cmds[1].cmd[0] = "infile",	n_cmds = 2, n_linker = 1

	< infile | grep i
	linker[0] = "<",			n_cmds = 0, n_linker = 1
	cmds[0].cmd[0] = "infile",	n_cmds = 1, n_linker = 1
	linker[1] = "|",			n_cmds = 1, n_linker = 2
	cmds[1].cmd[0] = "grep",	n_cmds = 2, n_linker = 2
	cmds[1].cmd[1] = "i",		n_cmds = 2, n_linker = 2
*/
void	assign_cmds_groups(t_minishell *data) 
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	printf("data->n_cmds: %d, data->n_linker: %d\n", data->n_cmds, data->n_linker);
	while (data->args[i])
	{
		if (data->args[i] && !is_linker(data->args[i]))
			data->cmds[j].cmd[k++] = data->args[i];
		else if (data->args[i])
		{
			data->linker[j++] = data->args[i];
			k = 0;
		}
		i++;
	}
}

/**
 * @brief Split the args array into groups of commands
 * @param t_minishell Structure representing the shared data and parameters.
 * @return 
 */
int		split_args_into_cmds(t_minishell *data)
{
	count_cmds_groups(data);
//	printf("%s, n_cmds: %d\n", data->prompt, n_cmds); //
	data->cmds = (t_cmd *)malloc((data->n_cmds + 1) * sizeof(t_cmd));
	if (!data->cmds)
		return (FAILURE);
	data->linker = (char **)malloc((data->n_linker + 1) * sizeof(char *));
	if (!data->linker)
		return (FAILURE);
//	if (data->args && assign_cmds_groups(data) == FAILURE)
//		return (FAILURE);
	if (data->args)
		assign_cmds_groups(data);

	return (SUCCESS);
}
