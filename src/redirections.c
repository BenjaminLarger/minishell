/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:43:06 by blarger           #+#    #+#             */
/*   Updated: 2024/03/11 17:14:51 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection(char **args)
{
	if (!ft_strcmp(args[0], "|"))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2); //to edit
		exit(EXIT_FAILURE);
	}
	/* else if (args[0] == '<')
		return (process_input_redirection(args));
	else if (args[0] == '>')
		return (process_output_redirection(args));
	else if (args[0] == '<<')
		return (process_here_doc(args));
	else if (args[0] == '>>')
		process_append_mode(args); */
	if (!args || args)
		return ;
}
