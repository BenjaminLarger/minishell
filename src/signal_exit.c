/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:30:46 by blarger           #+#    #+#             */
/*   Updated: 2024/03/12 16:20:04 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	printf("ppid: %d, pid: %d\n", getppid(), getpid());

static void	parent_exit_signal_handler(int sig)
{
	(void)sig;
	g_signal = exit_signal;
}

void	set_parent_exit_signal_action(void)
{
	signal(SIGUSR1, parent_exit_signal_handler);
}

static void	child_exit_signal_handler(int sig)
{
	(void)sig;
}

void	set_child_exit_signal_action(void)
{
	signal(SIGUSR1, child_exit_signal_handler);
}