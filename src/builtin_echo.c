/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:44:26 by blarger           #+#    #+#             */
/*   Updated: 2024/03/06 11:58:32 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **args, int n_cmd)
{
	bool	delete_newline;
	bool	start;
	int		i;

	start = true;
	i = 1;
	if (!ft_strncmp(args[i], "-n", 2))
	{
		i++;
		delete_newline = true;
	}
	else
		delete_newline = false;
	while (i <= n_cmd)
	{
		if (start == false)
			printf(" ");
		printf("%s", args[i]);
		i++;
		start = false;
	}
	if (delete_newline == false)
		printf("\n");
}
