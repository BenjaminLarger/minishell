/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redirections_handle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/03/15 21:19:34 by demre            ###   ########.fr       */
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
	write_fdin_to_fdout(data->fd_pipe1[READ_END], data->file.out_fd);
	close(data->file.out_fd);
}

static void	handle_input_redirection(t_minishell *data, char **args)
{
	data->file.in_fd = open(args[1], O_RDWR);
	if (data->file.in_fd < 0)
		perror("bash");
	data->fd_pipe1[READ_END] = data->file.in_fd;
}

static void	handle_here_document(t_minishell *data, char **args)
{
	int		pipefd[2];
	char	*line;

	if (is_linker(args[1]) == TRUE)
		perror_msg_kill_free(SYNTAX, data);
	if (pipe(pipefd) == -1)
		perror("pipe error:");
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, args[1]))
			break ;
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	data->fd_pipe1[READ_END] = pipefd[0];
}

/**
 * @brief Handle all redirections until next pipe or end-of-line.
 */
void	handle_redirections_until_next_pipe(t_minishell *data, char **args,
	int start, int end)
{
	int	i;

	i = start;
	while (i < end && args[i] && !ft_strcmp(args[i], "<"))
	{
		if (is_linker(args[i]) && args[i + 1] && is_linker(args[i + 1]))
			perror_msg_kill_free(TOKEN, data); // display args[i + 1]
		else if (!ft_strcmp(args[i], "<"))
			handle_input_redirection(data, args);
		else if (!ft_strcmp(args[i], ">"))
			handle_output_redirection(data, args);
		else if (!ft_strcmp(args[i], "<<"))
			handle_here_document(data, args);
		else if (!ft_strcmp(args[i], ">>"))
			handle_output_redirection(data, args);
		i++;
	}
}
