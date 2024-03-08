/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:07:07 by demre             #+#    #+#             */
/*   Updated: 2024/03/08 13:19:43 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print a string array to terminal
 * @param t_minishell Structure representing the shared data and parameters.
*/
void	print_array(char **array)
{
	int	i;
	
	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	print_all_cmds_and_linkers(t_minishell *data)
{
	int	i;
	int	j;

	printf("data->n_cmds: %d, data->n_linker: %d\n", data->n_cmds, data->n_linker);
	i = 0;
	while (i < data->n_cmds)
	{
		printf("data->cmds[%d].n_cmd_args : %d\n", i, data->cmds[i].n_cmd_args);
		j = 0;
		while (j < data->cmds[i].n_cmd_args + 1 && data->cmds[i].n_cmd_args > 0)
		{
			printf("data->cmds[%d].cmd[%d] : %s\n", i, j, data->cmds[i].cmd[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < data->n_linker + 1)
	{
		printf("linker[%d]: %s\n", i, data->linker[i]);
		i++;
	}
}

void	ft_leaks(void)
{
	system("leaks ./minishell");
}
