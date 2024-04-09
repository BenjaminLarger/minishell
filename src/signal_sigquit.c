/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sigquit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:18:30 by blarger           #+#    #+#             */
/*   Updated: 2024/04/09 13:25:49 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief if ctr \ is pressed after a command in interactive mode
 * 		=> error code = 131
 */
static void	child_sigquit_handler_after_prompt(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
	{
		g_signal = 130;
		printf("'^\\'Quit: %d\n", SIGQUIT);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void set_child_sigquit_action_after_prompt(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigquit_handler_after_prompt;
	sigaction(SIGQUIT, &act, NULL);
}

/**
 * @brief if ctr \ is pressed during a command in interactive mode
 * 		=> nothing happens
 */
static void	child_sigquit_handler_during_prompt(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void set_child_sigquit_action_during_prompt(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigquit_handler_during_prompt;
	sigaction(SIGQUIT, &act, NULL);
}
