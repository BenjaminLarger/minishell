/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redirections_handle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/18 13:12:20 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_output_redirection(t_minishell *data, char **args)
{
	if (data->file.has_outfile == TRUE)
		close(data->file.out_fd);
	if (!ft_strcmp(args[0], ">"))
		data->file.out_fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(args[0], ">>"))
		data->file.out_fd = open(args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->file.out_fd < 0)
	{
		perror("bash");
		// handle it
	}
	data->file.has_outfile = TRUE;
}

static void	handle_input_redirection(t_minishell *data, char **args)
{
	if (data->file.has_infile == TRUE)
		close(data->file.in_fd);
	data->file.in_fd = open(args[1], O_RDONLY);
	if (data->file.in_fd < 0)
	{
		perror("bash");
		// handle it
	}
	if (data->file.has_heredoc == TRUE)
	{
		close(data->file.heredoc_pipe[READ_END]);
		data->file.has_heredoc = FALSE;
	}
	data->file.has_infile = TRUE;
//	data->fd_pipe1[READ_END] = data->file.in_fd;
}

static void	handle_here_document(t_minishell *data, char **args)
{
	char	*line;
	
	print_array(args);
	if (is_linker(args[1]) == TRUE)
		perror_msg_kill_free(SYNTAX, data);

	if (data->file.has_heredoc == TRUE)
		close(data->file.heredoc_pipe[READ_END]);
	if (pipe(data->file.heredoc_pipe) == -1)
		perror("pipe error");
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, args[1]))
		{
			free(line);
			break;
		}
		write(data->file.heredoc_pipe[WRITE_END], line, strlen(line));
		write(data->file.heredoc_pipe[WRITE_END], "\n", 1);
		free(line);
	}
	close(data->file.heredoc_pipe[WRITE_END]);
//	data->fd_pipe1[READ_END] = pipefd[READ_END];

	if (data->file.has_infile == TRUE)
	{
		close(data->file.in_fd);
		data->file.has_infile = FALSE;
	}
	data->file.has_heredoc = TRUE;
//	data->file.in_fd = data->file.heredoc_pipe[READ_END];
//	data->fd_pipe1[READ_END] = data->file.heredoc_pipe[READ_END];
//	dup2(data->file.heredoc_pipe[READ_END], data->file.in_fd);
//	close(data->file.heredoc_pipe[READ_END]);

}

/**
 * @brief Update the pipe with the input from the infile of the last input 
 * redirection if this command group has an input redirection.
 */
void	update_pipe_with_infile(t_minishell *data)
{
	// Read from infile if there is one
	if (data->file.has_infile == TRUE)
	{
	//	data->fd_pipe1[READ_END] = data->file.in_fd;
		dup2(data->file.in_fd, data->fd_pipe1[READ_END]);
		close(data->file.in_fd);
	}
	if (data->file.has_heredoc == TRUE)
	{
	//	data->fd_pipe1[READ_END] = data->file.in_fd;
		data->fd_pipe1[READ_END] = data->file.heredoc_pipe[READ_END];
	//	dup2(data->file.heredoc_pipe[READ_END], data->fd_pipe1[READ_END]);
	//	close(data->file.heredoc_pipe[READ_END]);
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
