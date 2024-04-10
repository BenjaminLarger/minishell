/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 10:48:57 by blarger          ###   ########.fr       */
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
	set_child_sigint_action_during_prompt();
	set_child_sigquit_action_during_prompt();
	set_child_exit_signal_action(); //SIGUSR1 to delete ?
	//dprintf(2, "data->prompt: %s, data->is_exit: %d\n", data->prompt, data->is_exit);
	while (!(data->prompt) || data->is_exit == FALSE)
	{
		data->prompt = read_input(data->prompt);
		set_child_sigint_action_after_prompt();
		set_child_sigquit_action_after_prompt();
		if (g_signal != 0)
		{
			data->last_exit_status = g_signal;
			g_signal = 0;
		}
	//dprintf(2, "run_shell_loop data->prompt: %s, data->is_exit: %d\n", data->prompt, data->is_exit);
		if (data->prompt && *(data->prompt) && data->is_exit == FALSE
			&& !is_string_all_space(data->prompt))
		{
			if (split_input_into_args(data) == FAILURE)
				continue ; // errors handled and all freed
			if (check_tokens_syntax(data->args) == FAILURE)
				continue ; // errors handled and all freed
			if (data->n_args > 0)
			{
				if (exec_args(data) == FAILURE) // errors handled and all freed
				{
					free_string_array(data->args);
					continue ;
				}
				free_string_array(data->args);
			}
		}
		else if (!data->prompt) // when ctrl-d is pressed
		{
//			rl_replace_line("minish> exit", 0);
//			rl_redisplay();
			printf("contrl D pressed\n");
			printf("\e[31mexit\e[0m\n"); // to fix, not on same line
			dprintf(2, "shell exit status =%d\n", data->last_exit_status);
	//		kill(data->pid1, SIGUSR1); // delete ?
	//		exit(data->last_exit_status);
			return (SUCCESS);
		}
		set_child_sigint_action_during_prompt();
		set_child_sigquit_action_during_prompt();
	}
	if (data->prompt)
		free(data->prompt);
	dprintf(2, "exit son = %d\n", data->last_exit_status);
	printf("\e[31mexit\e[0m\n"); // keep
//	kill(data->pid1, SIGUSR1); // delete ?
//	exit(data->last_exit_status);
	return (SUCCESS);
}
