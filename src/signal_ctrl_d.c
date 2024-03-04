/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ctrl_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:30:46 by blarger           #+#    #+#             */
/*   Updated: 2024/03/04 18:33:13 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  If pid equals 0, then sig is sent to every process in the process
       group of the calling process. */

void		set_child_ctr_d_action(void)
{
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

void	kill_child_process(int sig)
{
	if (sig || !sig)
		rl_replace_line("minish> exit", 0);
	rl_redisplay ();
	exit(EXIT_SUCCESS);
}
