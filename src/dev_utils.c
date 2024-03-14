/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:07:07 by demre             #+#    #+#             */
/*   Updated: 2024/03/14 14:42:57 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

/**
 * @brief Print a string array to terminal
 * @param t_minishell Structure representing the shared data and parameters.
*/
void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("array[%d]: %s\n", i, array[i]);
		i++;
	}
	printf("array[%d]: %s\n", i, array[i]); // check NULL
}

void print_pipe_contents(int pipefd)
{
	char buffer[4096];
	ssize_t bytes_read;

	off_t current_pos = lseek(pipefd, 0, SEEK_CUR);
	if (current_pos == -1)
		perror("Failed to get file cursor position");
	fprintf(stderr, "Current position of file cursor: %ld\n", (long)current_pos);


	struct stat file_info;
	if (stat(".temp_pipex_heredoc", &file_info) == -1)
		perror("Failed to get file information");
	printf("File size of %s: %lld bytes\n", ".temp_pipex_heredoc", (long long)file_info.st_size);

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

void check_open_fd()
{
	int	fd;
	
	for (fd = 3; fd <= 6; fd++) {
		if (fcntl(fd, F_GETFD) != -1)
			fprintf(stderr, "fd %d open\n", fd);
		else
			fprintf(stderr, "fd %d closed\n", fd);
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
	dprintf(2, "data->fd_pipe1[READ_END]: %d, data->fd_pipe1[WRITE_END]: %d, data->fd_pipe2[READ_END]: %d, data->fd_pipe2[WRITE_END]: %d\n", data->fd_pipe1[READ_END], data->fd_pipe1[WRITE_END], data->fd_pipe2[READ_END], data->fd_pipe2[WRITE_END]);
}