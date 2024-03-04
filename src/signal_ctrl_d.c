/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ctrl_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:30:46 by blarger           #+#    #+#             */
/*   Updated: 2024/03/04 21:41:47 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  If pid equals 0, then sig is sent to every process in the process
       group of the calling process. */

void		set_child_ctr_d_action(void)
{
	printf("From set_child_ctr_d_action, pid: %d\n", getpid());
	signal(SIGUSR1, kill_child_process);
}

char	*ctrl_d_pushed(t_minishell *data) //doese not work
{
	rl_replace_line("exit", 0);
	rl_redisplay ();
	printf("exit");
	rl_on_new_line ();
	kill(data->pid1, SIGUSR1);
	free_string_array(&(data->prompt));
	exit(EXIT_SUCCESS);
	return (NULL);
}

void	kill_child_process(int sig) // en fait, ca kill le parent
{
//	if (sig || !sig)
//		printf("exit\n"); //should print exit next to the newline, not at the next line
	(void)sig;
	printf("From kill_child_process, pid: %d\n", getpid());
	exit(EXIT_SUCCESS);
}
