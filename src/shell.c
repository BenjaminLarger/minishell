/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/05 15:14:49 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_shell_loop(t_minishell *data)
{
	data->prompt = NULL;
	set_child_sigint_action();
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
			kill(data->pid1, SIGUSR1);
			exit(EXIT_SUCCESS);
	//		return (ctrl_d_pushed(pid1)); // => handle ctrl D ; must exit minishell && free the list => communicate to child process to stop the process
		}
	}
	if (data->prompt)
		free(data->prompt);
	printf("exit\n"); // bash rajoute un 'exit' quand on entre 'exit'
	kill(data->pid1, SIGUSR1);
	exit(EXIT_SUCCESS);
}
