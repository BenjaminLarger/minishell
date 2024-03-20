/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:35:15 by blarger           #+#    #+#             */
/*   Updated: 2024/03/20 19:10:17 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_env_variables(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		environ[i] = ft_strdup(environ[i]);
		i++;
	}
}
