/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redirections_handle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/17 17:14:56 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_output_redirection(t_minishell *data, char **args)
{
	if (!ft_strcmp(args[0], ">"))
		data->file.out_fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(args[0], ">>"))
		data->file.out_fd = open(args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->file.out_fd < 0)
		perror("bash");
	data->file.has_outfile = TRUE;
	write_fdin_to_fdout(data->fd_pipe1[READ_END], data->file.out_fd);
	close(data->file.out_fd);
}

static void	handle_input_redirection(t_minishell *data, char **args)
{
	if (data->file.has_infile == TRUE)
		close(data->file.in_fd);
	data->file.in_fd = open(args[1], O_RDWR);
	if (data->file.in_fd < 0)
	{
		perror("bash");
		// handle it
	}
	data->file.has_infile = TRUE;
//	data->fd_pipe1[READ_END] = data->file.in_fd;
}

static void	handle_here_document(t_minishell *data, char **args)
{
	int		pipefd[2];
	char	*line;

	if (is_linker(args[1]) == TRUE)
		perror_msg_kill_free(SYNTAX, data);
	if (pipe(pipefd) == -1)
		perror("pipe error");
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, args[1]))
			break ;
		write(pipefd[WRITE_END], line, strlen(line));
		write(pipefd[WRITE_END], "\n", 1);
		free(line);
	}
	close(pipefd[WRITE_END]);
	data->fd_pipe1[READ_END] = pipefd[READ_END];
}

void	update_pipe_with_infile(t_minishell *data)
{
	// Read from infile if there is one
	if (data->file.has_infile == TRUE)
	{
	//	data->fd_pipe1[READ_END] = data->file.in_fd;
		dup2(data->file.in_fd, data->fd_pipe1[READ_END]);
		close(data->file.in_fd);
	}
}

/**
 * @brief Handle all redirections until next pipe or end-of-line.
 */
void	handle_redirections_until_next_pipe(t_minishell *data, char **args,
	int start, int end)
{
	int	i;

	i = start;
	while (i < end && args[i])
	{
		if (is_linker(args[i]) && args[i + 1] && is_linker(args[i + 1]))
			perror_msg_kill_free(TOKEN, data); // display args[i + 1] in err
		else if (!ft_strcmp(args[i], "<"))
			handle_input_redirection(data, &args[i]);
		else if (!ft_strcmp(args[i], ">"))
			handle_output_redirection(data, &args[i]);
		else if (!ft_strcmp(args[i], "<<"))
			handle_here_document(data, &args[i]);
		else if (!ft_strcmp(args[i], ">>"))
			handle_output_redirection(data, &args[i]);
		i++;
	}
	update_pipe_with_infile(data);
}
