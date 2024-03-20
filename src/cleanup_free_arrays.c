/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_free_arrays.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:34:07 by demre             #+#    #+#             */
/*   Updated: 2024/03/20 19:12:30 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string_array(char **str_array)
{
	int	i;

	i = 0;
	if (str_array)
	{
		while (str_array[i])
		{
			free(str_array[i]);
			str_array[i] = NULL;
			i++;
		}
	}
	free(str_array);
}

void	free_n_string_array(char **str_array, int n)
{
	while (n > 0)
	{
		free(str_array[n - 1]);
		str_array[n - 1] = NULL;
		n--;
	}
	free(str_array);
}

void	free_array_string_array(char ***array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			free(array[i][j]);
			j++;
		}
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_env_array(void)
{
	extern char	**environ;
	int	i;

	i = 0;
	while (environ[i])
	{
		free(environ[i]);
		i++;
	}
}
