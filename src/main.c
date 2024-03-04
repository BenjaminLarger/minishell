/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:49 by demre             #+#    #+#             */
/*   Updated: 2024/03/04 15:35:20 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_unblock_sigquit = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	g_unblock_sigquit = 0;
	if (argc != 1 && argv && (envp || !envp))
		return (EXIT_FAILURE);
//		return (print_error(ARG), exit(EXIT_FAILURE));

	data.pid1 = fork();
	if (data.pid1 == -1)
		return (EXIT_FAILURE);//		error_and_exit(commands);
	else if (data.pid1 == 0)
		run_shell_loop(&data);
	else if (data.pid1 > 0)
	{
		set_child_ctr_d_action();
		signal_handling(data.pid1);
		waitpid(data.pid1, NULL, 0);
	}
	return (EXIT_SUCCESS);
}
