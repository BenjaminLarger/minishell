/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_handle_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:31:29 by demre             #+#    #+#             */
/*   Updated: 2024/03/02 16:30:36 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_prompt(char **prompt)
{
	while (!(*prompt) || ft_strcmp(*prompt, "exit") != 0)
	{
		*prompt = read_input(*prompt);
		if (process_input(prompt) == FAILURE)
			return (FAILURE);
	}
	free(*prompt);
	return (SUCCESS);
}
