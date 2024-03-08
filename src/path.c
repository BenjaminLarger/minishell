/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:12:28 by demre             #+#    #+#             */
/*   Updated: 2024/03/08 14:36:17 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_paths(char ***paths)
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
