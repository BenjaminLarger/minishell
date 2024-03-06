/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:19:52 by blarger           #+#    #+#             */
/*   Updated: 2024/03/06 11:00:01 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(void)
{
	extern char	**environ;
	char		**s;

	s = environ;
	while (*s)
	{
		printf("%s\n", *s);
		s++;
	}
}
