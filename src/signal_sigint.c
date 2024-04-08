/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:30:46 by demre             #+#    #+#             */
/*   Updated: 2024/04/08 18:19:04 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief if ctr c is pressed after a command in interactive mode
 * 		=> error code = 1
 */
static void	child_sigint_handler_during_prompt(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
		g_signal = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void set_child_sigint_action_during_prompt(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigint_handler_during_prompt;
	sigaction(SIGINT, &act, NULL);
}

static void	child_sigint_handler_after_prompt(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
		g_signal = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief if ctr c is pressed after a command in interactive mode
 * 		=> error code = 130
 */

void set_child_sigint_action_after_prompt(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigint_handler_after_prompt;
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
