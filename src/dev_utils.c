/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:07:07 by demre             #+#    #+#             */
/*   Updated: 2024/03/27 18:03:51 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

/**
 * @brief Print a string array to terminal
 * @param t_minishell Structure representing the shared data and parameters.
*/
void	print_array(char **array, char *message)
{
	int	i;

	if (message && ft_strlen(message) > 0)
		fprintf(stderr, "%s\n", message);

	i = 0;
	while (array[i])
	{
		dprintf(2, "array[%d]: %s\n", i, array[i]);
		i++;
	}
	dprintf(2, "array[%d]: %s\n", i, array[i]); // check NULL
}

void print_pipe_contents(int pipefd)
{
	char buffer[4096];
	ssize_t bytes_read;

	off_t current_pos = lseek(pipefd, 0, SEEK_CUR);
	if (current_pos == -1)
		perror("Failed to get file cursor position");
	fprintf(stderr, "Current position of file cursor: %ld\n", (long)current_pos);

	while ((bytes_read = read(pipefd, buffer, 4096)) > 0) {
		if (write(2, buffer, bytes_read) != bytes_read) {
			perror("write");
			break;
		}
		fprintf(stderr, "testtest\n");
		fprintf(stderr, "%s\n", buffer);
	}

		fprintf(stderr, "bytes_read: %zd\n", bytes_read);
	if (bytes_read == -1) {
		perror("read");
	}
}

void check_open_fd(char *message)
{
	int	fd;
	
	if (message && ft_strlen(message) > 0)
		fprintf(stderr, "%s\n", message);

	for (fd = 0; fd <= 6; fd++) {
		if (fcntl(fd, F_GETFD) != -1)
			dprintf(2, "fd %d open\n", fd);
		else
			dprintf(2, "fd %d closed\n", fd);
	}
}

void	print_fd(int fd)
{
	int		fd_dup;
	char	*print;

	fd_dup = dup(fd);
	dprintf(STDERR_FILENO, "\t\tFILE:");
	while (1)
	{
		print = ft_get_next_line(fd_dup);
		dprintf(STDERR_FILENO, "%s \n", print);
		if (!print)
			break ;
		free(print);
	}
	free(print);
}

void	print_pipes_fd(t_minishell *data)
{
	int i = 0;

	dprintf(2, "data->n_pid: %d\n", data->n_pid);
	while (i < data->n_pid)
	{
		dprintf(2, "data->fd_pipe[%d][READ_END]: %d, data->fd_pipe[%d][WRITE_END]: %d, ", i, data->fd_pipe[i][READ_END], i, data->fd_pipe[i][WRITE_END]);
		i++;
	}
	dprintf(2, "\n");

	dprintf(2, "data->file.in_fd: %d, data->file.out_fd: %d, data->file.heredoc_pipe[READ_END]: %d, data->file.heredoc_pipe[WRITE_END]: %d\n", data->file.in_fd, data->file.out_fd, data->file.heredoc_pipe[READ_END], data->file.heredoc_pipe[WRITE_END]);
}

void	print_files_fd(t_minishell *data)
{
	dprintf(2, "data->file.in_fd: %d, data->file.out_fd: %d, data->file.heredoc_pipe[READ_END]: %d, data->file.heredoc_pipe[WRITE_END]: %d\n", data->file.in_fd, data->file.out_fd, data->file.heredoc_pipe[READ_END], data->file.heredoc_pipe[WRITE_END]);
}
