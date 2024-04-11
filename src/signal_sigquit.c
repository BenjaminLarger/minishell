/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sigquit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:18:30 by blarger           #+#    #+#             */
/*   Updated: 2024/04/11 12:37:26 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termcap.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/* int clear_output(void)
{
    char *str = tgetstr("ccvrvrl", NULL); // Get the clear screen capability
    if (str != NULL) {
        tputs(str, 1, putchar); // Output the clear screen capability to the terminal
    }
    return 0;
} */

int	clear_output2(void)
{
	struct termios term;
    tcgetattr(STDIN_FILENO, &term); // Get current terminal attributes

    term.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Set modified attributes

    // Now you can read input character by character without echoing
    // Don't forget to restore terminal attributes later
    return 0;
}

/**
 * @brief if ctr \ is pressed after a command in interactive mode
 * 		=> error code = 131
 */
static void	child_sigquit_handler_after_prompt(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
	{
		g_signal = 131;
		printf("Quit: %d\n", SIGQUIT);
	}
}

void	set_child_sigquit_action_after_prompt(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigquit_handler_after_prompt;
	sigaction(SIGQUIT, &act, NULL);
}

/**
 * @brief Ignore on ctrl-\
 */
void	set_child_sigquit_action_during_prompt(void)
{
	signal(SIGQUIT, SIG_IGN);
}
