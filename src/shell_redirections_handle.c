/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redirections_handle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:17 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 18:13:02 by demre            ###   ########.fr       */
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
		data->last_exit_status = 1;
		print_strerror_and_arg(args[1]);
		return (FAILURE);
	}
	data->file.has_outfile = TRUE;
	return (SUCCESS);
}

static int	handle_input_redirection(t_minishell *data, char **args)
{
	if (data->file.has_infile == TRUE)
		close(data->file.in_fd);
	if (data->file.has_heredoc == TRUE)
	{
		close(data->file.heredoc_pipe[READ_END]);
		data->file.has_heredoc = FALSE;
	}
	data->file.has_infile = TRUE;
	data->file.in_fd = open(args[1], O_RDONLY);
	if (access(args[1], F_OK | R_OK) == -1 || data->file.in_fd < 0)
	{
		dprintf(2, "no infile, creating .temp_infile\n");
		data->file.in_fd = open(".temp_infile", O_RDONLY | O_CREAT, 0644);
		dup2(data->file.in_fd, STDIN_FILENO);
		close(data->file.in_fd);
		data->last_exit_status = 1;
		print_strerror_and_arg(args[1]);
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Update the pipe with the input from the infile of the last input 
 * redirection if this command group has an input redirection.
 */
static void	update_std_io_with_redirections(t_minishell *data)
{
	if (data->file.has_infile == TRUE)
	{
		dup2(data->file.in_fd, STDIN_FILENO);
		close(data->file.in_fd);
	}
	if (data->file.has_heredoc == TRUE)
	{
		dup2(data->file.heredoc_pipe[READ_END], STDIN_FILENO);
		close(data->file.heredoc_pipe[READ_END]);
	}
	if (data->file.has_outfile == TRUE)
	{
		dup2(data->file.out_fd, STDOUT_FILENO);
		close(data->file.out_fd);
	}
}

/**
 * @brief Handle all redirections until next pipe or end-of-line.
 */
int	handle_redirections(t_minishell *data, char **args, int start, int end)
{
	int	i;
	int	redirected;

	i = start;
	redirected = SUCCESS;
	while (i < end && args[i])
	{
		if (!ft_strcmp(args[i], "<"))
			redirected = handle_input_redirection(data, &args[i]);
		else if (!ft_strcmp(args[i], ">"))
			redirected = handle_output_redirection(data, &args[i]);
		else if (!ft_strcmp(args[i], "<<"))
			redirected = handle_here_document(data, &args[i]);
		else if (!ft_strcmp(args[i], ">>"))
			redirected = handle_output_redirection(data, &args[i]);
		if (redirected == FAILURE)
			return (FAILURE);
		i++;
	}
	update_std_io_with_redirections(data);
	return (SUCCESS);
}
