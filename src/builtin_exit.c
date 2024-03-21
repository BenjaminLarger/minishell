/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:57:45 by blarger           #+#    #+#             */
/*   Updated: 2024/03/21 09:59:37 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_minishell *data)
{
	dprintf(2, "HERE exit\n");
	if (command_with_pipe(data->args) == TRUE)
		return ;
	data->is_exit = TRUE;
	if (data->args[1])
		data->last_exit_status = 255;
}
