/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 20:42:33 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_shell_loop(t_minishell *data)
{
	set_child_sigint_action_during_prompt();
	set_child_sigquit_action_during_prompt();
	data->cd_last_dir[0] = '\0'; //test if needed
	while (!(data->prompt) || data->is_exit == FALSE)
	{
		data->prompt = read_input(data->prompt);
		set_child_sigint_action_after_prompt();
		set_child_sigquit_action_after_prompt();
		if (g_signal != 0)
		{
			printf("\tlast exit status f_signal run shell\n");
			data->last_exit_status = g_signal;
			g_signal = 0;
		}
		if (data->prompt && *(data->prompt) && data->is_exit == FALSE
			&& !is_string_all_space(data->prompt))
		{
			if (split_input_into_args(data) == FAILURE)
				continue ;
			if (check_tokens_syntax(data->args) == FAILURE)
				continue ;
			if (data->n_args > 0)
			{
				if (exec_args(data) == FAILURE)
				{
					free_string_array(data->args);
					continue ;
				}
				free_string_array(data->args);
			}
		}
		else if (!data->prompt)
		{
			printf("\e[31mexit\e[0m\n"); // to fix, not on same line
			dprintf(2, "shell exit status =%d\n", data->last_exit_status);
			return (SUCCESS);
		}
		set_child_sigint_action_during_prompt();
		set_child_sigquit_action_during_prompt();
	}
	if (data->prompt)
		free(data->prompt);
	dprintf(2, "exit son = %d\n", data->last_exit_status);
	printf("\e[31mexit\e[0m\n"); // keep
	return (SUCCESS);
}
