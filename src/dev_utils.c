/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:07:07 by demre             #+#    #+#             */
/*   Updated: 2024/03/13 19:32:00 by demre            ###   ########.fr       */
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
