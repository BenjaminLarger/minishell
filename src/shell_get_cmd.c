/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_get_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:35:01 by demre             #+#    #+#             */
/*   Updated: 2024/03/15 21:41:23 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Save the command and its parameters to cmd array by removing 
 * redirection indicators and the associated filenames from command group 
 * (until next pipe or end-of-line). 
 */
void	get_cmd_without_redirections(t_minishell *data, char ***cmd,
	int start, int end)
{
	int	i;
	int	j;
	int	cmd_args_count;

	i = start;
	cmd_args_count = 0;
	while (i < end && data->args[i])
	{
		if (!is_linker(data->args[i]))
			cmd_args_count++;
		else if (is_linker(data->args[i]))
			i++;
		i++;
	}
	dprintf(STDERR_FILENO, "\nstart %d, end %d, cmd_args_count %d\n", start, end, cmd_args_count); //
	*cmd = (char **)malloc((cmd_args_count + 1) * sizeof(char *));
	if (!(*cmd))
		return ; // malloc failure
	i = start;
	j = 0;
	while (j < cmd_args_count)
	{
		if (!is_linker(data->args[i]))
		{
			(*cmd)[j] = ft_strdup(data->args[i]);
			if (!(*cmd))
			{
				free_n_string_array(cmd, j);
				return ; // malloc failure
			}
//		dprintf(STDERR_FILENO, "data->args[%d] %p\n", i, data->args[i]); //
//		dprintf(STDERR_FILENO, "(*cmd)[%d] %p\n", j, (*cmd)[j]); //
			j++;
		}
		else if (is_linker(data->args[i]))
			i++;
		i++;
	}
	(*cmd)[j] = NULL;
}
