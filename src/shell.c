/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/04 16:33:43 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_sigint_handler(int sig)
{
	if (sig || !sig)
		rl_on_new_line ();
	rl_redisplay ();
}

static void set_child_sigint_action(void)
{
	struct sigaction	act;
	//struct sigaction	cat;

	ft_bzero(&act, sizeof(act));
	//ft_bzero(&cat, sizeof(cat));
	act.sa_handler = &child_sigint_handler;
	/* cat.sa_handler = &child_sigint_handler;
	cat.sa_flags = SA_SIGINFO; */
	sigaction(SIGINT, &act, NULL);
	//sigaction(SIGINT, &cat, NULL);
}

int	run_shell_loop(t_minishell *data)
{
	data->prompt = NULL;
	set_child_sigint_action();
	while (!(data->prompt) || ft_strcmp(data->prompt, "exit") != 0)
	{
		data->prompt = read_input(data->prompt, data->pid1);
		if (split_input(data) == FAILURE)
			return (FAILURE);
		process_args(data);
		free_string_array(data->args); // check if correct
	}
	free(data->prompt);
	return (SUCCESS);
}
