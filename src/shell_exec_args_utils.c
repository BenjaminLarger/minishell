/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 19:04:17 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_args_init(t_minishell *data, int *i, int *start)
{
	*i = 0;
	*start = 0;
	data->original_stdin_fd = dup(STDIN_FILENO);
	data->original_stdout_fd = dup(STDOUT_FILENO);
	data->n_pid = 0;
	// add realloc
	data->pid = (int *)malloc(1000 * sizeof(int));
	if (!data->pid)
		return (FAILURE);
	data->status = (int *)malloc(1000 * sizeof(int));
	if (!data->status)
		return (FAILURE);
	return (SUCCESS);
}
