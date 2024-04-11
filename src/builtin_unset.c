/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:57:23 by blarger           #+#    #+#             */
/*   Updated: 2024/04/11 11:13:39 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/**
 * @brief Moves the env var at index 'i' in the 'env_msh' array to the end of
 * the array and sets it to NULL.
 * @note The element at index 'i' is dynamically allocated and is  freed 
 * before setting it to NULL. The elements following 'i' are shifted one 
 * position down in the array.
 */
static void	move_unset_to_the_end(t_minishell *data, int i, int arr_len)
{
	free(data->env_msh[i]);
	while (i < arr_len - 1)
	{
		data->env_msh[i] = data->env_msh[i + 1];
		i++;
	}
	data->env_msh[i] = NULL;
}

static int	value_is_valid(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (!(ft_isalpha(value[i])) && !(ft_isalnum(value[i]))
			&& value[i] != '_')
		{
			ft_putstr_fd("minish: unset: `", 2);
			ft_putstr_fd(value, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static void	compare_and_remove(char **args, t_minishell *data, int i)
{
	int		j;

	j = 0;
	while (data->env_msh[j])
	{
		if (!(ft_strncmp(args[i], data->env_msh[j], ft_strlen(args[i])))
			&& data->env_msh[j][ft_strlen(args[i])] == '=')
		{
			move_unset_to_the_end(data, j, array_len(data->env_msh));
			return ;
		}
		j++;
	}
}

void	builtin_unset(char **args, t_minishell *data)
{
	int		i;

	i = 1;
	data->last_exit_status = 0;
	if (command_with_pipe(data->args) == TRUE)
		return ;
	while (args[i])
	{
		if (value_is_valid(args[i]) == FALSE)
		{
			i++;
			continue ;
		}
		compare_and_remove(args, data, i);
		i++;
	}
}

/* 
void	builtin_unset(char **args, t_minishell *data)
{
	int		i;
	int		j;

	i = 1;
	data->last_exit_status = 0;
	while (args[i])
	{
		j = 0;
		if (value_is_valid(args[i]) == FALSE)
		{
			i++;
			continue ;
		}
		while (data->env_msh[j])
		{
			if (!(ft_strncmp(args[i], data->env_msh[j], ft_strlen(args[i])))
				&& data->env_msh[j][ft_strlen(args[i])] == '=')
			{
				move_unset_to_the_end(data, j, array_len(data->env_msh));
				break ;
			}
			j++;
		}
		i++;
	}
} */
