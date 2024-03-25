/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:34:57 by blarger           #+#    #+#             */
/*   Updated: 2024/03/25 20:44:41 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//#define SEPARATOR "="

char	**concat_and_add_env(char **env_msh, char *new_content)
{
	char	**new_env;
	int		i;
	int		actual_env_len;

	if (!(ft_strchr(new_content, '=')) || ft_strlen(new_content) < 3
		|| new_content[ft_strlen(new_content) - 1] == '=')
		return (env_msh);
	actual_env_len = 0;
	while (env_msh[actual_env_len])
		actual_env_len++;
	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (actual_env_len + 2));
	if (!new_env)
		return (NULL); //Hanlde malloc failure
	while (i < actual_env_len)
	{
		new_env[i] = ft_strdup(env_msh[i]);
		free(env_msh[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_content);
	i++;
	new_env[i] = NULL;
	return (new_env);
}

/* 
static void	display_exported_variable(t_minishell *data)
{
	extern char	**environ;
	char		**s;

	s = environ;
	while (*s)
	{
		printf("declare -x %s\n", *s);
		s++;
	}
}
 */

static void	display_exported_variable(t_minishell *data)
{
	int	i;
	
	i = 0;
	while (data->env_msh[i])
	{
		printf("declare -x %s\n", data->env_msh[i]);
		i++;
	}
}


void	builtin_export(char **args, t_minishell *data)
{
	int	i;

	i = 1;
	if (!args[1])
		return (display_exported_variable(data));
	else if (command_with_pipe(data->args) == TRUE)
		return ;
	else
	{
		while (args[i])
		{
			data->env_msh = concat_and_add_env(data->env_msh, args[i]);
			i++;
		}
	}
}