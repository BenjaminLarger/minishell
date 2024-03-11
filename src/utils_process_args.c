/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:35 by blarger           #+#    #+#             */
/*   Updated: 2024/03/11 17:07:48 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_minishell *data)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (data->args[i])
	{
		if (!ft_strcmp(data->args[i], "|"))
			count++;
		i++;
	}
	return (count);
}

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

int	get_next_pipe(char **args)
{
	int	i;

	i = 0;
	while (args[i] && is_linker(args[i]) == FALSE)
		i++;
	if (args[i] && !ft_strcmp(args[i], "|"))
		i++;
	return (i);
}
