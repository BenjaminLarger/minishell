/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/12 12:25:12 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	kill_and_exit(t_minishell *data, int exit_type)
{
	kill(data->pid1, SIGUSR1);
	if (exit_type == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (exit_type == EXIT_FAILURE)
	{
		perror("Tokenization failed");
		exit(EXIT_FAILURE);
	}

}

int	run_shell_loop(t_minishell *data)
{
	data->prompt = NULL;
	set_child_sigint_action();
	while (!(data->prompt) || ft_strcmp(data->prompt, "exit") != 0)
	{
		data->prompt = read_input(data->prompt);
		if (data->prompt)
		{
			if (split_input_into_args(data) == FAILURE)
				kill_and_exit(data, EXIT_FAILURE); // free first
			process_args(data); // error: two consecutive linker or sole linker
		//	exec_args(data);
			free_string_array(data->args);
		}
		else // when ctrl-d is pressed
		{
//			rl_replace_line("minish> exit", 0);
//			rl_redisplay();
//			sleep(2);
			printf("contrl D pressed\n");
			printf("exit\n");
			kill(data->pid1, SIGUSR1);
			printf("signal sent\n"); // to delete
			exit(EXIT_SUCCESS);
		}
	}
	if (data->prompt)
		free(data->prompt);
	printf("exit\n"); // keep
	kill(data->pid1, SIGUSR1);
	printf("signal sent\n"); // to delete
	exit(EXIT_SUCCESS);
}
