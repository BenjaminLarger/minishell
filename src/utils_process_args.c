/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:35 by blarger           #+#    #+#             */
/*   Updated: 2024/03/12 12:15:26 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_linker(char *str)
{
	if (ft_strcmp(str, "|") == 0
		|| ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0
	)
		return (TRUE);
	return (FALSE);
}
int	count_arg_after_cmd(char **args)
{
	int	n;

	n = 0;
	while (args[n] && is_linker(args[n]) == FALSE)
		n++;
	printf("n = %d\n", n);
	return (n);
}
