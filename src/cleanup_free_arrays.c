/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_free_arrays.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:34:07 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 14:21:20 by blarger          ###   ########.fr       */
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

void	free_int_array(int **int_array, int size)
{
	int	i;

	i = 0;
	if (int_array)
	{
		while (i < size)
		{
			free(int_array[i]);
			int_array[i] = NULL;
			i++;
		}
	}
	free(int_array);
}
