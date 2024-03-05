/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:44:26 by blarger           #+#    #+#             */
/*   Updated: 2024/03/05 12:59:08 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(t_minishell *data, int i)
{
	bool	delete_newline;
	bool	start;

	start = true;
	if (!ft_strncmp(data->args[i], "-n", 2))
		delete_newline = true;
	else
		delete_newline = false;
	while (data->args[i] != "|" && data->args[i] != "||"
		&& data->args[i])
	{
		if (start == false)
			printf(" ");
		printf("%s", data->args[i]);
	}
	if (delete_newline == false)
		printf("\n");
}
