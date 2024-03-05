/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:30:46 by blarger           #+#    #+#             */
/*   Updated: 2024/03/05 15:15:33 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_exit_signal_handler(int sig)
{
	(void)sig;
//	printf("From kill_child_process, pid: %d\n", getpid());
	g_signal = exit_signal;
}

void	set_parent_exit_signal_action(t_minishell *data)
{
	data->is_exit = FALSE;
//	printf("From set_child_ctr_d_action, pid: %d\n", getpid());
	signal(SIGUSR1, parent_exit_signal_handler);
}
