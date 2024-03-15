/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/15 21:36:06 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_args(t_minishell *data)
{
	int		i;
	int		start_index;
	char	**cmd;

	i = 0;
	start_index = 0;
	print_array(data->args); //
	while (i < data->n_args && data->args[i]) // && data->args[i + 1])
	{
		start_index = i;
		while (data->args[i] && ft_strcmp(data->args[i], "|"))
			i++;
		dprintf(STDERR_FILENO, "\nPipe or eof at i = %d\n", i); //

		handle_redirections_until_next_pipe(data, data->args, start_index, i);
		get_cmd_without_redirections(data, &cmd, start_index, i);
		if (cmd && *cmd)
			exec_command(data, cmd);
		free_string_array(cmd);
		i++;
	}
	write_fdin_to_fdout(data->fd_pipe1[READ_END], STDOUT_FILENO);
}
