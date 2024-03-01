/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:49 by demre             #+#    #+#             */
/*   Updated: 2024/03/01 13:40:27 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	static char	*prompt = NULL;

	if (argc != 1 && argv && (envp || !envp))
		return (EXIT_FAILURE);
//		return (print_error(ARG), exit(EXIT_FAILURE));

	while (!prompt || ft_strcmp(prompt, "exit") != 0)
	{
		prompt = read_input(prompt);
//		printf("%s, %zu\n", prompt, ft_strlen(prompt));
	}
	
	
	free(prompt);

	return (EXIT_SUCCESS);
}
