/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:58:59 by blarger           #+#    #+#             */
/*   Updated: 2024/03/12 17:27:16 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_linker(char *linker)
{
	if (ft_strncmp(linker, "|", 1) == 0)
		return ("`|'");
	else if (ft_strncmp(linker, "<", 1) == 0)
		return ("`<'");
	else if (ft_strncmp(linker, "<<", 2) == 0)
		return ("`<<'");
	else if (ft_strncmp(linker, ">", 1) == 0)
		return ("`<<'");
	else if (ft_strncmp(linker, ">>", 2) == 0)
		return ("`>>'");
	return (NULL);
}

void	perror_msg_kill_free(char *msg, t_minishell *data)
{
	/* if (msg && msg[0] != '\0')
		perror(msg); */
	if (errno && msg)
	{
		free_string_array(data->args);
		kill(data->pid1, SIGUSR1);
		exit(errno);
	}
	else
	{
		kill(data->pid1, SIGUSR1);
		exit(errno);
	}
}
