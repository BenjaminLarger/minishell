/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:43:06 by blarger           #+#    #+#             */
/*   Updated: 2024/03/19 19:48:07 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DO_NO_EXIT 10

/* !!! When doing a dup2, program act as if ctrl D was pressed */
static int	process_here_doc(char **args, t_minishell *data)
{
	int		pipefd[2];
	char	*line;
	//char	buffer[1024];

	if (is_linker(args[1]) == TRUE)
		perror_msg_kill_free(SYNTAX, data);
	if (pipe(pipefd) == -1)
	{
		data->file.exit_status = errno;
		perror("pipe error:");
	}
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, args[1]))
			break ;
		write (pipefd[1], line, strlen(line));
		write (pipefd[1], "\n", 1);
		free(line);
	}
	close (pipefd[1]);
	//does not crash with dup2(STDOUT_FILENO, STDIN_FILENO);
	data->fd_pipe1[READ_END] = pipefd[0];
	/* read(pipefd[0], buffer, sizeof(buffer));
	printf ("buffer here: %s\n", buffer); */
	//close(pipefd[0]);
	return (2);
}

// Hedge case: > outfile => ask for input // ls | > outfile => works

static int	process_output(char **args, t_minishell *data)
{
	if (is_linker(args[1]) == TRUE)
		perror_msg_kill_free(SYNTAX, data); // err mais pas exit
	if (!ft_strcmp(args[0], ">"))
		data->file.out_fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(args[0], ">>"))
		data->file.out_fd = open(args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->file.out_fd < 0 || access(args[1], W_OK) == -1)
	{
		data->file.exit_status = errno;
		perror("bash");
	}
	write_fdin_to_fdout(data->fd_pipe1[READ_END], data->file.out_fd);
	close(data->file.out_fd);
	rl_on_new_line();
	return (2);
}

static int	process_input(char **args, t_minishell *data)
{
	if (is_linker(args[1]) == TRUE)
		perror_msg_kill_free(TOKEN, data);
	data->file.in_fd = open(args[1], O_RDWR);
	if (data->file.in_fd < 0 || access(args[1], F_OK) == -1
		|| access(args[1], R_OK) == -1)
	{
		data->file.exit_status = errno;
		perror("bash");
		//msg_kill_free(args[1], FILE, DO_NO_EXIT, data); perror handle error message => edit function
	}
	/* print_fd(data->file.in_fd);
	dup2(data->file.in_fd, STDIN_FILENO);
	dup2(data->file.in_fd, data->fd_pipe1[WRITE_END]); */
	data->fd_pipe1[READ_END] = data->file.in_fd;
	rl_on_new_line();
	return (2);
}

int	handle_redirection(char **args, t_minishell *data)
{
	/* if (!ft_strcmp(args[0], "|"))
		perror_msg_kill_free(TOKEN, data); */
	data->file.exit_status = 0;
	if (!ft_strcmp(args[0], "<"))
		return (process_input(args, data));
	else if (!ft_strcmp(args[0], ">"))
		return (process_output(args, data));
	else if (!ft_strcmp(args[0], "<<"))
		return (process_here_doc(args, data));
	else if (!ft_strcmp(args[0], ">>"))
		return (process_output(args, data));
	return (0);
}
