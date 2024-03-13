/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:19:52 by blarger           #+#    #+#             */
/*   Updated: 2024/03/13 16:18:47 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(void)
{
	extern char	**environ;
	char		**s;

	s = environ;
	// add return if non valid command after env
	while (*s)
	{
		printf("%s\n", *s);
		s++;
	}
}
