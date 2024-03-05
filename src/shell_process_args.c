/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:44:40 by demre             #+#    #+#             */
/*   Updated: 2024/03/05 16:49:59 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_args(t_minishell *data)
{
//	if (split_args_into_cmds(data) == FAILURE)
//		return (FAILURE);

	if (!ft_strncmp(data->args[1], "<<", 2))
		process_here_file(data, 2);
	else if (!ft_strncmp(data->args[0], "echo", 4))
		echo_builtin(data, 1);
	return (SUCCESS);
}
