/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:49 by demre             #+#    #+#             */
/*   Updated: 2024/04/09 17:00:06 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	if (argc != 1 && argv)
		exit(EXIT_SUCCESS);
	if (load_env_variables(&data, envp) == FAILURE
		|| init_program(&data) == FAILURE)
		exit(EXIT_FAILURE);
	dprintf(2, "\e[36mLaunching minishell - $SHLVL=%s\e[0m\n", ft_getenv(&data, "SHLVL"));
	run_shell_loop(&data);

	dprintf(2, "freeing\n");
	free_string_array(data.env_msh);
	free(data.cd_last_dir);
	exit(data.last_exit_status);
}
