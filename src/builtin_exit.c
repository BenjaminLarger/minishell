/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:57:45 by blarger           #+#    #+#             */
/*   Updated: 2024/03/19 13:23:16 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_minishell *data)
{
	if (command_with_pipe(data->args) == TRUE)
		return ;
	data->is_exit = TRUE;
}

/* int	is_exit(char *cmd)
{
	int	i;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (strncmp("exit", &cmd[i], 4))
		i += 4;
	else
		return (FALSE);
	while (ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '\0')
		return (FALSE);
	return (TRUE);
} */