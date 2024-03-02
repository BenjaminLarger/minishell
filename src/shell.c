/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/02 21:40:29 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_shell_loop(t_mish *mish)
{
	mish->prompt = NULL;
	while (!(mish->prompt) || ft_strcmp(mish->prompt, "exit") != 0)
	{
		mish->prompt = read_input(mish->prompt);
		if (split_input(mish) == FAILURE)
			return (FAILURE);
		
		process_args(mish);

		free_string_array(mish->args); // check if correct
	}
	free(mish->prompt);
	return (SUCCESS);
}
