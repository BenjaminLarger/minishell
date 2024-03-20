/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:34:57 by blarger           #+#    #+#             */
/*   Updated: 2024/03/20 19:29:40 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SEPARATOR "="

char	**concat_and_add_env(char **env, char *new_content)
{
	char	**new_env;
	int		i;
	int		actual_env_len;

	if (!(ft_strchr(new_content, '=')) || ft_strlen(new_content) < 3
		|| new_content[ft_strlen(new_content) - 1] == '=')
		return (env);
	actual_env_len = 0;
	while (env[actual_env_len])
		actual_env_len++;
	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (actual_env_len + 2));
	if (!new_env)
		return (NULL); //Hanlde malloc failure
	while (i < actual_env_len)
	{
		new_env[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_content);
	i++;
	new_env[i] = NULL;
	return (new_env);
}

static void	display_exported_variable(void)
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

void	builtin_export(char **args, t_minishell *data)
{
	int	i;
	extern char	**environ;

	i = 1;
	if (!args[1])
		return (display_exported_variable());
	else if (command_with_pipe(data->args) == TRUE)
		return ;
	else
	{
		while (args[i])
		{
			environ = concat_and_add_env(environ, args[i]);
			i++;
		}
	}
}