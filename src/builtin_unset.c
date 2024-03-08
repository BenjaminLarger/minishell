/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:57:23 by blarger           #+#    #+#             */
/*   Updated: 2024/03/08 13:03:33 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_unset_to_the_end(char **environ, int i, int arr_len);
static int	array_len(char **array);

/* LOGIC
There isn't a specific function to remove an env variable allowed by
the subject. The trick here would be to search the arg in the env variable
(using extern char **environ). If arg belongs to environ, then we move the string
at the end of the array. Then we attribute this value to NULL.

LEAKS
env variable are not supposed to be allocated via malloc => to check.
*/

void	builtin_unset(char **args)
{
	int			i;
	int			j;
	extern char	**environ;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (environ[j] != NULL)
		{
			if (!(ft_strncmp(args[i], environ[j], ft_strlen(args[i])))
				&& environ[j][ft_strlen(environ[j])] != '=')
			{
				move_unset_to_the_end(environ, j, array_len(environ));
				break ;
			}
			j++;
		}
		i++;
	}
}

static int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

static void	move_unset_to_the_end(char **environ, int i, int arr_len)
{
	while (i < arr_len - 1)
	{
		environ[i] = environ[i + 1];
		ft_strlcpy(environ[i], environ[i + 1], ft_strlen(environ[i + 1]) + 1);
		i++;
	}
	environ[i] = NULL;
}
