/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:35 by blarger           #+#    #+#             */
/*   Updated: 2024/03/19 12:15:51 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a string only consists of whitespace
 * @param str 
 * @return (1) if TRUE, (0) otherwise
 */
int	is_string_all_space(char const *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (ft_isspace((unsigned char)*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

/**
 * @brief Checks if a given string is a redirection linker.
 * @return Returns TRUE (1) if str is '|', '<', '<<', '>', '>>', otherwise 
 * returns FALSE (0).
 */
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

/**
 * @brief Writes to fd_out after reading from fd_in
 */
void	write_fdin_to_fdout(int fd_in, int fd_out)
{
	char	buffer[4096];
	ssize_t	bytes_read;

	dprintf(STDERR_FILENO, "write_fdin_to_fdout, fd_in: %d, fd_out: %d\n", fd_in, fd_out); //
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd_in, buffer, sizeof(buffer));
		dprintf(STDERR_FILENO, "write_fdin_to_fdout bytes_read:%zd\n", bytes_read); //
		if (bytes_read < 0)
		{
			perror("read from pipe error");
			
			exit(EXIT_FAILURE);
		}
		write(fd_out, buffer, bytes_read);
	}
}

int	command_with_pipe(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp("|", args[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}