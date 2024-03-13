/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/13 18:33:02 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	kill_and_exit(t_minishell *data, int exit_status)
{
	// free args
	// close file descriptors
	kill(data->pid1, SIGUSR1);
	if (errno == 0)
		exit(exit_status);
	exit(errno);
}

int	run_shell_loop(t_minishell *data)
{
	data->prompt = NULL;
	set_child_sigint_action();
	set_child_exit_signal_action();
	while (!(data->prompt) || ft_strcmp(data->prompt, "exit") != 0)
	{
		data->prompt = read_input(data->prompt);
		if (data->prompt && *(data->prompt) && ft_strcmp(data->prompt, "exit"))
		{
			if (split_input_into_args(data) == FAILURE)
				kill_and_exit(data, EXIT_FAILURE); // malloc or other failure
		//	if (process_args(data) == FAILURE)
		//		kill_and_exit(data, errno);
			exec_args(data);
			free_string_array(data->args);
		}
		else if (!data->prompt) // when ctrl-d is pressed
		{
//			rl_replace_line("minish> exit", 0);
//			rl_redisplay();
//			sleep(2);
			printf("contrl D pressed\n");
			printf("exit\n"); // to fix, not on same line
			kill(data->pid1, SIGUSR1);
			exit(EXIT_SUCCESS);
		}
	}
	if (data->prompt)
		free(data->prompt);
	printf("exit\n"); // keep
	kill(data->pid1, SIGUSR1);
	exit(EXIT_SUCCESS);
}
