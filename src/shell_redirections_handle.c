/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redirections_handle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/04/03 20:22:26 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_output_redirection(t_minishell *data, char **args)
{
	if (data->file.has_outfile == TRUE)
		close(data->file.out_fd);
	if (!ft_strcmp(args[0], ">>"))
		data->file.out_fd = open(args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(args[0], ">"))
		data->file.out_fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(args[1], W_OK) == -1 || data->file.out_fd < 0)
	{
		data->last_exit_status = 0;
		display_error(args[1]);
		return (FAILURE);
	}
	data->file.has_outfile = TRUE;
	dup2(data->file.out_fd, STDOUT_FILENO);
	close(data->file.out_fd);
	return (SUCCESS);
}

static int	handle_input_redirection(t_minishell *data, char **args)
{
	if (data->file.has_infile == TRUE)
		close(data->file.in_fd);
	data->file.in_fd = open(args[1], O_RDONLY);
	if (access(args[1], F_OK) == -1 || access(args[1], R_OK) == -1
		|| data->file.in_fd < 0)
	{
		data->last_exit_status = 1;
		display_error(args[1]);
		return (FAILURE);
	}
	if (data->file.has_heredoc == TRUE)
	{
		close(data->file.heredoc_pipe[READ_END]);
		data->file.has_heredoc = FALSE;
	}
	data->file.has_infile = TRUE;
	return (SUCCESS);
}

/**
 * @brief Update the pipe with the input from the infile of the last input 
 * redirection if this command group has an input redirection.
 */
void	update_pipe_with_infile(t_minishell *data)
{
//	dprintf(2, "update_pipe_with_infile\n");
//	print_pipes_fd(data);
	if (data->file.has_infile == TRUE)
	{
//		dup2(data->file.in_fd, data->fd_pipe1[READ_END]);
//		dup2(data->file.in_fd, data->fd_pipe[data->n_pid][READ_END]);
		dup2(data->file.in_fd, STDIN_FILENO);
		close(data->file.in_fd);
	}
	if (data->file.has_heredoc == TRUE)
	{
	//	close(data->fd_pipe1[READ_END]);
	//	data->fd_pipe1[READ_END] = data->file.heredoc_pipe[READ_END];

//		close(data->fd_pipe[data->n_pid][READ_END]);
//		data->fd_pipe[data->n_pid][READ_END] = data->file.heredoc_pipe[READ_END];
		dup2(data->file.heredoc_pipe[READ_END], STDIN_FILENO);
		close(data->file.heredoc_pipe[READ_END]);

	}
}

/**
 * @brief Handle all redirections until next pipe or end-of-line.
 */
int	handle_redirections(t_minishell *data, char **args, int start, int end)
{
	int	i;
	int	is_success;

	i = start;
	is_success = 0;
	while (i < end && args[i])
	{
		if (!ft_strcmp(args[i], "<"))
			is_success = handle_input_redirection(data, &args[i]);
		else if (!ft_strcmp(args[i], ">"))
			is_success = handle_output_redirection(data, &args[i]);
		else if (!ft_strcmp(args[i], "<<"))
			is_success = handle_here_document(data, &args[i]);
		else if (!ft_strcmp(args[i], ">>"))
			is_success = handle_output_redirection(data, &args[i]);
		i++;
	}
	update_pipe_with_infile(data);
	return (is_success);
}
