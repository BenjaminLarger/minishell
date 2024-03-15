/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:04:16 by demre             #+#    #+#             */
/*   Updated: 2024/03/15 21:34:20 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute cmd if it is a builtin command
 * @param cmd command with its parameters
 * @return SUCCESS if cmd correctly executed, FAILURE otherwise
 */
int	exec_cmd_if_builtin(char **args)
{
	if (args)
	{
//		int i = 0;
//		while (args[i])
//		{
//			dprintf(STDERR_FILENO, "args[%d]: %s\n", i, args[i]); // delete
//			i++;
//		}
		return (FAILURE);
	}
	else
		return (SUCCESS);
}
