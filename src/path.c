/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:12:28 by demre             #+#    #+#             */
/*   Updated: 2024/03/15 21:28:45 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Retrieves the directories listed in the PATH environment variable
 * and appends a forward slash to each path.
 */
static int	get_all_paths_from_env(char ***paths)
{
	char	*all_paths_as_one_str;
	char	*temp;
	int		i;
	
	all_paths_as_one_str = getenv("PATH");
	if (!all_paths_as_one_str)
		all_paths_as_one_str = "";
	*paths = ft_split(all_paths_as_one_str, ':');
	if (!(*paths))
		return (FAILURE);
	i = 0;
	while ((*paths)[i])
	{
		temp = ft_strjoin((*paths)[i], "/");
		if (!temp)
		{
			free_n_string_array(*paths, i);
			free(paths);
			return (FAILURE);
		}
		free((*paths)[i]);
		(*paths)[i++] = temp;
	}
	(*paths)[i] = NULL;
	return (SUCCESS);
}

static int	test_path_with_command(char *path, char const *cmd)
{
	char	*temp;
	int		has_access;

	temp = ft_strjoin(path, cmd);
	if (!temp)
		exit(EXIT_FAILURE);
	has_access = access(temp, F_OK | X_OK);
	free(temp);
	if (has_access != -1)
		return (SUCCESS);
	else
		return (FAILURE);
}

static int	add_path_to_command(char const *cmd, char **cmd_with_path, char **paths, int n_paths)
{
	int		i;

	i = 0;
	while (paths[i] && test_path_with_command(paths[i], cmd) == FAILURE)
		i++;
	if (i != n_paths && ft_strchr(cmd, '/') == NULL)
	{
		*cmd_with_path = ft_strjoin(paths[i], cmd);
		if (!(*cmd_with_path))
			return (FAILURE);
	}
	else
		*cmd_with_path = ft_strdup(cmd);
	return (SUCCESS);
}

/**
 * @brief Retrieves the full path of a command executable `cmd` in the 
 * directories specified by the PATH environment variable. If found, it saves 
 * the full path of the command in the `cmd_with_path` parameter.
 * @return Returns SUCCESS (0) if the command is found and its full path is 
 * retrieved successfully, otherwise returns FAILURE (1).
 */
int	get_cmd_with_path(char const *cmd, char **cmd_with_path)
{
	char	**paths;
	int		n_paths;

	if (get_all_paths_from_env(&paths) != SUCCESS)
	{
		perror("Error loading paths");
		return (FAILURE);
	}
	n_paths = 0;
	while (paths[n_paths])
		n_paths++;
	if (add_path_to_command(cmd, cmd_with_path, paths, n_paths) != SUCCESS)
	{
		perror("Memory allocation failure");
		free_string_array(paths);
		return (FAILURE);
	}
	free_string_array(paths);
	return (SUCCESS);
}
