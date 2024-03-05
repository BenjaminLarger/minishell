/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:00:30 by demre             #+#    #+#             */
/*   Updated: 2024/03/05 16:52:13 by demre            ###   ########.fr       */
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

static void	count_cmds_groups(t_minishell *data)
{
	int		i;

	data->n_cmds = 0;
	data->n_linker = 0;
	i = 0;
	while (data->args[i])
	{
		if (!is_linker(data->args[i]))
			data->n_cmds++;
		else
			data->n_linker++;
		i++;
	}
}

int	assign_cmds_groups(t_minishell *data)
{
	if (data)
		return (FAILURE);
	return (SUCCESS);
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
	if (data->args && assign_cmds_groups(data) == FAILURE)
		return (FAILURE);

	return (SUCCESS);
}
