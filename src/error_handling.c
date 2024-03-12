/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:58:59 by blarger           #+#    #+#             */
/*   Updated: 2024/03/12 11:10:34 by blarger          ###   ########.fr       */
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

void	msg_kill_free(char *m, char *s, int ex, t_minishell *d)
{
	perror(m);
	if (s && s[0] != '\0')
		perror(s);
	if (ex == EXIT_SUCCESS)
	{
		//free here
		kill(d->pid1, SIGUSR1);
		exit(EXIT_SUCCESS);
	}
	else if (ex == EXIT_FAILURE)
	{
		//free here
		kill(d->pid1, SIGUSR1);
		exit(EXIT_FAILURE);
	}
}
