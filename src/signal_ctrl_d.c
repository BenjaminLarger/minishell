/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ctrl_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:30:46 by blarger           #+#    #+#             */
/*   Updated: 2024/03/04 12:48:57 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  If pid equals 0, then sig is sent to every process in the process
       group of the calling process. */

void		set_child_ctr_d_action(void)
{
	signal(SIGUSR1, kill_child_process);
}

char	*ctrl_d_pushed(pid_t pid1)
{
	kill(pid1, SIGUSR1);
	//free(...);
	exit(EXIT_SUCCESS);
	return (NULL);
}

void	kill_child_process(int sig)
{
	if (sig || !sig)
		printf("exit\n"); //should print exit next to the newline, not at the next line
	exit(EXIT_SUCCESS);
}
