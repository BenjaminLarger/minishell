/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/04 21:41:46 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_sigint_handler(int sig)
{
	(void)sig;
	printf("ctrl-c caught in child\n"); //
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void set_child_sigint_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

int	run_shell_loop(t_minishell *data)
{
	data->prompt = NULL;
	set_child_sigint_action();
	printf("From child, ppid: %d, pid: %d\n", getppid(), getpid()); //
	while (!(data->prompt) || ft_strcmp(data->prompt, "exit") != 0)
	{
		data->prompt = read_input(data->prompt);
		if (data->prompt)
		{
			if (split_input_in_args(data) == FAILURE)
				return (FAILURE);
			process_args(data);
			free_string_array(data->args);
		}
		else // when ctrl-d is pressed
		{
//			rl_replace_line("minish> exit", 0);
//			rl_redisplay();
//			sleep(2);
			printf("exit\n");
			printf("from child: ctrl-d pressed, exiting child with SUCCESS\n");
			kill(data->pid1, SIGUSR1);
			exit(EXIT_SUCCESS);
	//		return (ctrl_d_pushed(pid1)); // => handle ctrl D ; must exit minishell && free the list => communicate to child process to stop the process
		}
	}
	if (data->prompt)
		free(data->prompt);
	printf("exit\n"); // bash rajoute un 'exit' quand on entre 'exit'
	printf("from child: exited run_shell_loop, exiting child with SUCCESS\n");
	kill(data->pid1, SIGUSR1);
	exit(EXIT_SUCCESS);
}
