/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:35 by blarger           #+#    #+#             */
/*   Updated: 2024/03/14 14:14:03 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_linker(char *str)
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
int	count_commands(char **args)
{
	int	n;

	n = 0;
	while (args[n] && is_linker(args[n]) == FALSE)
		n++;
	printf("n = %d\n", n);
	return (n);
}

void	write_fdin_to_fdout(int fd_in, int fd_out)
{
	char	buffer[4096];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd_in, buffer, sizeof(buffer));
		dprintf(STDERR_FILENO, "HERE bytes_read:%zd\n", bytes_read);
		if (bytes_read < 0)
		{
			perror("read from pipe error");
			exit(EXIT_FAILURE);
		}
		write(fd_out, buffer, bytes_read);
	}
}
