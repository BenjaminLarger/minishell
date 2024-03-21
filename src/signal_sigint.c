/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:30:46 by demre             #+#    #+#             */
/*   Updated: 2024/03/21 16:36:06 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_sigint_handler(int sig)
{
	(void)sig;
//	printf("ctrl-c caught in child\n"); //
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void set_child_sigint_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

static void	parent_sigint_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	block_signal(SIGINT);
	g_signal = ctrlc_signal;
	unblock_signal(SIGINT);
}

/* The sigaction struct is used to specify the action to be taken when a
signal is received.
 bzero ensures that any fields not explicity set will have a default value of
 zero.
 act.sa_handler = &sigint_handler;: Specifies the signal handler function
 to be called when the SIGINT signal (Ctrl-C) is received.
 sigaction(SIGINT, &act, NULL);: Associates the specified action (act) with
 the SIGINT signal. */

void	set_parent_sigint_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &parent_sigint_handler;
	sigaction(SIGINT, &act, NULL);
}
