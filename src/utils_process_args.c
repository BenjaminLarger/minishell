/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:35 by blarger           #+#    #+#             */
/*   Updated: 2024/03/27 15:59:40 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a string only consists of whitespace
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
int	is_linker(char *str)
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

int	is_redirection(char *str)
{
	if (ft_strcmp(str, "<") == 0
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
		dprintf(STDERR_FILENO, "\e[34mwrite_fdin_to_fdout bytes_read:%zd\n\e[0m", bytes_read); //
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

/**
 * @brief Checks if a character is valid to name an environment variable.
 * Valid characters include alphanumeric characters (a-z, A-Z, 0-9) and 
 * underscore (_).
 * @param c The character to be checked.
 * @return TRUE (1) if the character is valid, FALSE (0) otherwise.
 */
int	is_valid_ev_character(char c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c == '_'))
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Get the value associated with a given environment variable key.
 * @param data A pointer to the structure containing environment variables.
 * @param key The key (variable name) to search for in the environment 
 * variables.
 * @return A pointer to the 'value' associated with the given 'key' if found,
 * NULL otherwise.
 */
char	*ft_getenv(t_minishell *data, char *key)
{
	int	i;
	
	i = 0;
	while (data->env_msh[i])
	{
		if (ft_strncmp(data->env_msh[i], key, ft_strlen(key)) == 0)
		{
			return (ft_strchr(data->env_msh[i], '=') + 1);
		}
		i++;
	}
	return (NULL);
}

#include <stdlib.h>
#include <string.h> // For memcpy

char	**realloc_char_array(char **ptr, int old_size, int new_size)
{
	char	**new_ptr;
	int		copy_size;

	if (!ptr)
	{
		// If ptr is NULL, realloc behaves like malloc
		return ((char **)malloc(new_size * sizeof(char *)));
	}
	else if (new_size == 0)
	{
		free_string_array(ptr);
		return (NULL);
	}
	else
	{
		// Allocate new memory block for the array of pointers
		new_ptr = (char **)malloc(new_size * sizeof(char *));
		if (!new_ptr)
			return (NULL); // Malloc failed

		// Determine how many pointers to copy
		copy_size = (old_size < new_size) ? old_size : new_size;

		// Copy the pointers
		ft_memcpy(new_ptr, ptr, copy_size * sizeof(char *));

		// Free the old array of pointers (but not the strings themselves)
		free(ptr);
		return (new_ptr);
	}
}
