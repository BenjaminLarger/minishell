/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_herefile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:52:17 by blarger           #+#    #+#             */
/*   Updated: 2024/04/10 17:08:03 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_sigint_handler_herefile(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

static void	father_sigint_handler_herefile(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
		g_signal = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void set_child_sigint_action_herefile(void)
{
	struct sigaction	act;

	if (isatty(STDIN_FILENO))
		g_signal = 1;
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigint_handler_herefile;
	sigaction(SIGINT, &act, NULL);
}

void	set_father_sigint_action_herefile(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &father_sigint_handler_herefile;
	sigaction(SIGINT, &act, NULL);
}
