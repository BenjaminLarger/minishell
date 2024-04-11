/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/04/11 11:43:51 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_exit_and_success(void)
{
	ft_putstr_fd("exit\n", 1);
	return (SUCCESS);
}

static void	ask_prmpt_and_reset_signals_after_pompt(t_minishell *data)
{
	data->prompt = read_input(data->prompt);
	set_child_sigint_action_after_prompt();
	set_child_sigquit_action_after_prompt();
	if (g_signal != 0)
	{
		data->last_exit_status = g_signal;
		g_signal = 0;
	}
}

static int	free_and_success(t_minishell *data)
{
	if (data->prompt)
		free(data->prompt);
	return (SUCCESS);
}

int	run_shell_loop(t_minishell *data)
{
	while (!(data->prompt) || data->is_exit == FALSE)
	{
		ask_prmpt_and_reset_signals_after_pompt(data);
		if (data->prompt && *(data->prompt) && data->is_exit == FALSE
			&& !is_string_all_space(data->prompt))
		{
			if (split_input_into_args(data) == FAILURE
				|| check_tokens_syntax(data->args) == FAILURE)
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
			return (print_exit_and_success());
		set_child_sigint_action_during_prompt();
		set_child_sigquit_action_during_prompt();
	}
	return (free_and_success(data));
}
