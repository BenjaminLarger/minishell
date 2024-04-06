/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/04/06 12:49:07 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	kill_and_exit(t_minishell *data, int exit_status)
{
	// free args
	// close file descriptors
	free_env_array();
	close(data->fd_pipe1[READ_END]);
	kill(data->pid1, SIGUSR1);
	if (errno == 0)
		exit(exit_status);
	exit(errno);
} */

int	run_shell_loop(t_minishell *data)
{
	set_child_sigint_action();
	set_child_exit_signal_action();
	//dprintf(2, "data->prompt: %s, data->is_exit: %d\n", data->prompt, data->is_exit);
	while (!(data->prompt) || data->is_exit == FALSE)
	{
		data->prompt = read_input(data->prompt);
	//dprintf(2, "run_shell_loop data->prompt: %s, data->is_exit: %d\n", data->prompt, data->is_exit);
		if (data->prompt && *(data->prompt) && data->is_exit == FALSE
			&& !is_string_all_space(data->prompt))
		{
			if (check_if_last_element_is_pipe(data) == FAILURE)
				continue ;
			if (split_input_into_args(data) == FAILURE)
				continue ; // malloc or single quote
			if (check_tokens_syntax(data->args) == FAILURE)
				continue ; // syntax error
			if (data->n_args > 0)
			{
				if (exec_args(data) == FAILURE)
				{
					free_string_array(data->args);
					//print_error ?
					continue ;
				//	kill_and_exit(data, errno);
					//kill_and_exit(data, data->last_exit_status);
					//kill_and_exit(data, EXIT_FAILURE); // malloc failure
				}
				free_string_array(data->args);
			}
		}
		else if (!data->prompt) // when ctrl-d is pressed
		{
//			rl_replace_line("minish> exit", 0);
//			rl_redisplay();
//			sleep(2);
//			free_env_array(); only in main enough?
			printf("contrl D pressed\n");
//			close(data->fd_pipe1[READ_END]);
			printf("\e[31mexit\e[0m\n"); // to fix, not on same line
			dprintf(2, "shell exit status =%d\n", data->last_exit_status);
			kill(data->pid1, SIGUSR1);
			exit(data->last_exit_status);
		}
	}
	if (data->prompt)
		free(data->prompt);
	dprintf(2, "exit son = %d\n", data->last_exit_status);
//	close(data->fd_pipe1[READ_END]);
//	free_env_array(); only in main enough?
	printf("\e[31mexit\e[0m\n"); // keep
	kill(data->pid1, SIGUSR1);
	exit(data->last_exit_status);
}
