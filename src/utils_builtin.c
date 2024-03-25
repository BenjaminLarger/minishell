/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:35:15 by blarger           #+#    #+#             */
/*   Updated: 2024/03/25 19:33:34 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Increase by one the $SHLVL environment variable that holds the current
 * shell's number of shell levels
 */
static void	increase_shlvl(char **env_msh)
{
	int		i;
	char	*temp_shlvl;

	i = 0;
	while (env_msh[i])
	{
		if (ft_strncmp(env_msh[i], "SHLVL=", 6) == 0)
		{
			printf("found $SHLVL%s\n", ft_strchr(env_msh[i], '='));
			temp_shlvl
				= ft_itoa(ft_atoi(ft_strchr(env_msh[i], '=') + 1) + 1);
//			if (!temp_shlvl)
//			{
//				print_error(malloc failure);
//				return ;
//			}
			free(env_msh[i]);
			env_msh[i] = ft_strjoin("SHLVL=", temp_shlvl);
			free(temp_shlvl);
			printf("env_msh[i]: %s\n", env_msh[i]);
			break ;
		}
		i++;
	}
}

/**
 * @brief Save envp that was passed as an argument to main to data->env_msh
 */
void	malloc_env_variables(t_minishell *data, char **envp)
{
	int			i;
	int			size;

	i = 0;
	size = 0;
	while (envp[size])
		size++;
	data->env_msh = (char **)malloc((size + 1) * sizeof(char *));
	while (i < size)
	{
		data->env_msh[i] = ft_strdup(envp[i]);
		i++;
	}
	data->env_msh[i] = NULL;
	increase_shlvl(data->env_msh);
}
