/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/07 16:18:45 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_linker(char *str)
{
	if (ft_strcmp(str, "|") == 0
		|| ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0
	)
		return (TRUE);
	return (FALSE);
}

void	exec_command(t_minishell *data, char **args, int start, int end)
{
	int	pid2;

	pid2 = fork();
//	if (pid2 == -1)
//		display_error_and_exit("Fork error", commands);
	if (pid2 == 0)
	{
		args[end] = NULL;
		dup2(data->fd_pipe1[0], STDIN_FILENO); // READ_END
//		dup2(data->fd_pipe2[1], STDOUT_FILENO); // WRITE_END
		close(data->fd_pipe1[0]); // READ_END
//		close(data->fd_pipe2[1]); // WRITE_END
		fprintf(2, "executing: %s\n", args[start]); // delete
		execve(args[start], args, NULL); // add envp
//		handle_exec_error(args[start]);
		exit(EXIT_FAILURE);
	}
	else if (pid2 > 0)
	{
		close(data->fd_pipe1[0]); // READ_END
		close(data->fd_pipe2[1]); // WRITE_END
		waitpid(pid2, NULL, 0);
	}
}

void	exec_args(t_minishell *data)
{
	int i = 0;
	int start_index = 0;

	while (data->args[i] && data->args[i + 1])
	{
		start_index = i;
		while (data->args[i] && !is_linker(data->args[i]))
			i++;
		// linker at i, beginning of cmd at start_index
		if (ft_strcmp(data->args[i], "|") == 0)
		{
			fprintf(2, "args[start_index]: %s\n", data->args[start_index]); //
			if (pipe(data->fd_pipe2) == -1)
				return ; // handle error
	//			display_error_and_exit("Pipe error", commands);
			exec_command(data, data->args, start_index, i);
			data->fd_pipe1[0] = data->fd_pipe2[0]; // READ_END
		}
		i++;
	}
}
