/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:18:40 by blarger           #+#    #+#             */
/*   Updated: 2024/03/10 09:40:22 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ERROR -1

static char	*replace_name_by_value(char *name);
static char *return_null_mallocated(char *name);

/* IMPORTANT
getenv does not return a mallocated string

PRINCIPLE
If args[i] start by "$", we search for its corresponding value,
and swap it if we find it.
If the corresponding value does not exist, we return a single '\0'
mallocated. */

void	handle_env_variable(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			args[i] = replace_name_by_value(args[i]);
		}
		i++;
	}
}

static char	*replace_name_by_value(char *name)
{
	char	*value;
	char	*to_copy;

	to_copy = getenv(name + 1);
	if (!to_copy)
		return (return_null_mallocated(name));
	value = (char *)malloc(sizeof(char) * (ft_strlen(to_copy) + 1));
	if (!value)
		return (NULL);//handle malloc failure
	ft_strlcpy(value, getenv(name + 1), ft_strlen(to_copy) + 1);
	free(name);
	return (value);
}

static char *return_null_mallocated(char *name)
{
	char	*value;

	value = (char *)ft_calloc(sizeof(char), 1);
	if (!value)
		return (NULL); //Handle malloc failure
	free(name);
	return (value);
}

