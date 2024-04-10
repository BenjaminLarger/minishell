/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 20:25:42 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*custom_realloc(int *ptr, int old_size, int new_size)
{
	int	*new_ptr;

	if (!ptr)
		return ((int *)malloc(new_size * sizeof(int)));
	new_ptr = (int *)malloc(new_size * sizeof(int));
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

void	increase_pid_number(t_minishell *data)
{
	int	*new_pid;
	int	*new_status;

	data->n_pid++;
	if (data->n_pid >= data->pid_alloc_size - 2)
	{
		new_pid = custom_realloc(data->pid, data->pid_alloc_size,
				data->pid_alloc_size * 2);
		new_status = custom_realloc(data->status, data->pid_alloc_size,
				data->pid_alloc_size * 2);
		if (new_pid && new_status)
		{
			data->pid = new_pid;
			data->status = new_status;
		}
		else
		{
			print_strerror_and_set_exit_status(data);
			free(data->pid);
			free(data->status);
			data->pid = NULL;
			data->status = NULL;
		}
		data->pid_alloc_size *= 2;
	}
}

int	exec_args_init(t_minishell *data, int *i, int *start)
{
	*i = 0;
	*start = 0;
	data->original_stdin_fd = dup(STDIN_FILENO);
	data->original_stdout_fd = dup(STDOUT_FILENO);
	data->n_pid = 0;
	data->pid_alloc_size = 20;
	data->pid = (int *)malloc(data->pid_alloc_size * sizeof(int));
	if (!data->pid)
		return (FAILURE);
	data->status = (int *)malloc(data->pid_alloc_size * sizeof(int));
	if (!data->status)
		return (FAILURE);
	return (SUCCESS);
}
