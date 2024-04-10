/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:35 by blarger           #+#    #+#             */
/*   Updated: 2024/04/10 16:21:28 by demre            ###   ########.fr       */
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

/**
 * @brief Check if the given array of arguments contains a pipe operator '|'.
 * @param args An array of strings representing the command arguments.
 * @return int Returns TRUE (1) if the command contains a pipe operator,
 * FALSE (0) otherwise.
 */
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
		if ((ft_strncmp(data->env_msh[i], key, ft_strlen(key)) == 0)
			&& data->env_msh[i][ft_strlen(key)] == '=')
		{
			return (ft_strchr(data->env_msh[i], '=') + 1);
		}
		i++;
	}
	return (NULL);
}
