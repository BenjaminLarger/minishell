/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/04 12:56:36 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_sigint_handler(int sig)
{
	if (sig || !sig)
		printf("Hello from the shell\n");
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
