/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/03 13:14:24 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigusr1(int sig)
{
	if (sig || !sig)
		printf("Hello from the shell\n");
}

static void set_sigusr1_action(void)
{
	struct sigaction	act;

	bzero(&act, sizeof(act)); //ft_
	act.sa_handler = &handle_sigusr1;
	sigaction(SIGINT, &act, NULL);
}

int	run_shell_loop(t_minishell *data)
{
	data->prompt = NULL;
	set_sigusr1_action();
	while (!(data->prompt) || ft_strcmp(data->prompt, "exit") != 0)
	{
		data->prompt = read_input(data->prompt);
		if (split_input(data) == FAILURE)
			return (FAILURE);
		
		process_args(data);

		free_string_array(data->args); // check if correct
	}
	free(data->prompt);
	return (SUCCESS);
}
