/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:57:23 by blarger           #+#    #+#             */
/*   Updated: 2024/04/06 15:54:13 by demre            ###   ########.fr       */
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

void	builtin_unset(char **args, t_minishell *data)
{
	int		i;
	int		j;

	i = 1;
	while (args[i])
	{
		j = 0;
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
}
