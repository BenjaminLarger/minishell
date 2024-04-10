/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:30:46 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 16:26:29 by demre            ###   ########.fr       */
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

void	set_child_sigint_action_during_prompt(void)
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
void	set_child_sigint_action_after_prompt(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigint_handler_after_prompt;
	sigaction(SIGINT, &act, NULL);
}
