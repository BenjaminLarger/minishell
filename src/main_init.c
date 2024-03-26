/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:35:15 by blarger           #+#    #+#             */
/*   Updated: 2024/03/26 11:15:57 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Increase by one the $SHLVL environment variable that holds the current
 * shell's number of shell levels
 */
static int	increase_shlvl(char **env_msh)
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
			if (!temp_shlvl)
				return (print_error_and_failure(MALLOC_FAIL));
			free(env_msh[i]);
			env_msh[i] = ft_strjoin("SHLVL=", temp_shlvl);
			if (!env_msh[i])
			{
				free(temp_shlvl);
				free_n_string_array(env_msh, i);
				return (print_error_and_failure(MALLOC_FAIL));
			}
			free(temp_shlvl);
			break ;
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Save envp that was passed as an argument to main to data->env_msh
 */
int	load_env_variables(t_minishell *data, char **envp)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (envp[size])
		size++;
	data->env_msh = (char **)malloc((size + 1) * sizeof(char *));
	if (!data->env_msh)
		return (print_error_and_failure(MALLOC_FAIL));
	while (i < size)
	{
		data->env_msh[i] = ft_strdup(envp[i]);
		i++;
	}
	data->env_msh[i] = NULL;
	if (increase_shlvl(data->env_msh) == FAILURE)
	{
		free(data->env_msh);
		return (print_error_and_failure(MALLOC_FAIL));
	}
	return (SUCCESS);
}

int	init_program(t_minishell *data)
{
	data->cd_last_dir = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
	if (!data->cd_last_dir)
		return (print_error_and_failure(MALLOC_FAIL));
	if (pipe(data->fd_pipe1) == -1)
		return (print_error_and_failure(PIPE));
	close(data->fd_pipe1[WRITE_END]);
	data->last_exit_status = 0;
	data->prompt = NULL;
	data->is_exit = FALSE;
	return (SUCCESS);
}
