/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:35:15 by blarger           #+#    #+#             */
/*   Updated: 2024/04/10 20:39:25 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_array_size(char **envp)
{
	int	size;

	size = 0;
	if (!envp)
		return (size);
	while (envp[size])
		size++;
	return (size);
}

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
			temp_shlvl = ft_itoa(ft_atoi(ft_strchr(env_msh[i], '=') + 1) + 1);
			if (!temp_shlvl)
				return (print_error_and_failure(MALLOC_FAIL));
			free(env_msh[i]);
			env_msh[i] = ft_strjoin("SHLVL=", temp_shlvl);
			if (!env_msh[i])
			{
				free(temp_shlvl);
				free_n_string_array(env_msh, i);
				return (FAILURE);
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
	size = get_array_size(envp);
	data->env_msh = (char **)malloc((size + 1) * sizeof(char *));
	if (!data->env_msh)
		return (print_error_and_failure(MALLOC_FAIL));
	while (i < size)
	{
		data->env_msh[i] = ft_strdup(envp[i]);
		if (!data->env_msh[i])
		{
			free_n_string_array(data->env_msh, i);
			return (print_error_and_failure(MALLOC_FAIL));
		}
		i++;
	}
	data->env_msh[i] = NULL;
	if (increase_shlvl(data->env_msh) == FAILURE)
	{
		free_string_array(data->env_msh);
		return (print_error_and_failure(MALLOC_FAIL));
	}
	return (SUCCESS);
}

int	init_program(t_minishell *data)
{
	data->cd_last_dir = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
	if (!data->cd_last_dir)
		return (print_error_and_failure(MALLOC_FAIL));
	data->last_exit_status = 0;
	data->prompt = NULL;
	data->is_exit = FALSE;
	data->n_pid = 0;
	data->pid_alloc_size = 20;
	data->no_output_builtin_executed = FALSE;
	return (SUCCESS);
}
