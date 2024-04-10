/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_update.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:35:34 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 14:50:13 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds a new environment variable to the array of environment variables 
 * by reallocating memory for a new environment variables array.
 * @return SUCCESS if the addition was successful, FAILURE otherwise.
 */
int	new_shell_var(char ***env_msh, char *new_var)
{
	int		old_size;
	char	**temp_env;

	temp_env = *env_msh;
	old_size = 0;
	while (temp_env[old_size])
		old_size++;
	*env_msh = (char **)malloc((old_size + 2) * sizeof(char *));
	if (!(*env_msh))
		return (FAILURE);
	ft_memcpy(*env_msh, temp_env, old_size * sizeof(char *));
	(*env_msh)[old_size] = ft_strdup(new_var);
	if (!(*env_msh)[old_size])
		return (FAILURE);
	(*env_msh)[old_size + 1] = NULL;
	free(temp_env);
	return (SUCCESS);
}

/**
 * @brief Replaces an existing environment variable with a new value in the 
 * env_msh array in place.
 * @return SUCCESS if the replacement was successful, FAILURE otherwise.
 */
int	replace_shell_var(char ***env_msh, char *new_var, int end)
{
	int		i;
	char	*temp_env;

	i = 0;
	while ((*env_msh)[i])
	{
		if (ft_memcmp((*env_msh)[i], new_var, end) == 0
			&& (*env_msh)[i][end] == '=')
		{
			temp_env = ft_strdup(new_var);
			if (!temp_env)
				return (FAILURE);
			free((*env_msh)[i]);
			(*env_msh)[i] = temp_env;
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

/**
 * @brief Adds a new environment variable to the array of environment variables
 * without using the '+=' syntax.
 * @return SUCCESS if the addition was successful, FAILURE otherwise.
 */
int	new_shell_var_without_plus(char ***env_msh, char *new_var, int end)
{
	int		old_size;
	char	**temp_env_array;
	int		len_new_var;

	temp_env_array = *env_msh;
	old_size = 0;
	while (temp_env_array[old_size])
		old_size++;
	*env_msh = (char **)malloc((old_size + 2) * sizeof(char *));
	if (!(*env_msh))
		return (FAILURE);
	ft_memcpy(*env_msh, temp_env_array, old_size * sizeof(char *));
	len_new_var = ft_strlen(new_var);
	(*env_msh)[old_size] = (char *)malloc(len_new_var * sizeof(char));
	if (!(*env_msh)[old_size])
		return (FAILURE);
	ft_memcpy((*env_msh)[old_size], new_var, end);
	(*env_msh)[old_size][end] = '=';
	ft_memcpy((*env_msh)[old_size] + end + 1, new_var + end + 2,
		len_new_var - end + 2);
	(*env_msh)[old_size][len_new_var - 1] = '\0';
	(*env_msh)[old_size + 1] = NULL;
	free(temp_env_array);
	return (SUCCESS);
}

/**
 * @brief Appends a value to an existing environment variable in place.
 * @return SUCCESS if the appending was successful, FAILURE otherwise.
 */
int	append_shell_var(char ***env_msh, char *new_var, int end)
{
	int		i;

	i = 0;
	while ((*env_msh)[i])
	{
		if (ft_memcmp((*env_msh)[i], new_var, end) == 0
			&& (*env_msh)[i][end] == '=')
		{
			(*env_msh)[i] = ft_strjoin_free(
					(*env_msh)[i], ft_strchr(new_var, '=') + 1);
			if (!(*env_msh)[i])
				return (FAILURE);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}
int	is_valid_shell_value(char *arg, t_minishell *data)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	i--;
	while (arg[i] != '=' && is_valid_value_character(arg[i]) == TRUE && i > 0)
	{
		i--;
	}
	if (arg[i] != '=' )
	{
		print_error_message_and_arg(IDENTIFIER, arg);
		return (return_true_or_false_set_exit_status(FALSE, 1, data));
	}
	while (i > 0)
	{
		i--;
		if (arg[i] == '=')
		{
			print_error_message_and_arg(IDENTIFIER, arg);
			return (return_true_or_false_set_exit_status(FALSE, 1, data));
		}
	}
	return (TRUE);
}
