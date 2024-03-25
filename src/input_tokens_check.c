/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokens_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:36:58 by demre             #+#    #+#             */
/*   Updated: 2024/03/25 13:56:27 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *error, char *arg)
{
	ft_putstr_fd(error, 2);
	if (arg)
		ft_putstr_fd(get_linker_for_error(arg), 2);
	else
		ft_putstr_fd("`newline'", 2);
	ft_putchar_fd('\n', 2);
}

int	check_tokens_syntax(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (is_linker(args[i]) && !args[i + 1])
		{
			print_error(SYNTAX, NULL);
			return (FAILURE);
		}
//		else if (ft_strcmp(args[i], "|"))
		if (is_redirection(args[i])
			&& args[i + 1] && is_redirection(args[i + 1]))
		{
			print_error(SYNTAX, args[i + 1]);
			return (FAILURE);
		}
		/* 
		else if (!ft_strcmp(args[i], "<"))
			is_success = handle_input_redirection(data, &args[i]);
		else if (!ft_strcmp(args[i], ">"))
			is_success = handle_output_redirection(data, &args[i]);
		else if (!ft_strcmp(args[i], "<<"))
			is_success = handle_here_document(data, &args[i]);
		else if (!ft_strcmp(args[i], ">>"))
			is_success = handle_output_redirection(data, &args[i]); */
		i++;
	}
	return (SUCCESS);
}
