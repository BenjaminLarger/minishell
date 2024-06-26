/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:44:26 by blarger           #+#    #+#             */
/*   Updated: 2024/04/05 14:17:54 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(char **args, bool start, int i, bool delete_newline)
{
	while (args[i] && is_linker(args[i]) == FALSE)
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

void	builtin_echo(char **args)
{
	bool	delete_newline;
	bool	start;
	int		i;

	i = 1;
	start = true;
	if (!args[1] || args[1][0] == '\0')
		return ((void)printf("\n"));
	if (!args[1] || args[1][0] == '\0')
		return ((void)printf("\n"));
	if (!ft_strncmp(args[i], "-n", 2))
	{
		i++;
		delete_newline = true;
	}
	else
		delete_newline = false;
	print_echo(args, start, i, delete_newline);
}
