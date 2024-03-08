/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:30:46 by blarger           #+#    #+#             */
/*   Updated: 2024/03/08 17:58:47 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_exit_signal_handler(int sig)
{
	(void)sig;
//	printf("From parent_exit_signal_handler, pid: %d\n", getpid());
	g_signal = exit_signal;
}

void	set_parent_exit_signal_action(void)
{
//	printf("From set_parent_exit_signal_action, pid: %d\n", getpid());
	signal(SIGUSR1, parent_exit_signal_handler);
}
