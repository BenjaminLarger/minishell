/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:58:59 by blarger           #+#    #+#             */
/*   Updated: 2024/03/26 10:56:06 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_linker_for_error(char *linker)
{
	if (ft_strncmp(linker, "|", 1) == 0)
		return ("`|'");
	else if (ft_strncmp(linker, "<<", 2) == 0)
		return ("`<<'");
	else if (ft_strncmp(linker, "<", 1) == 0)
		return ("`<'");
	else if (ft_strncmp(linker, ">>", 2) == 0)
		return ("`>>'");
	else if (ft_strncmp(linker, ">", 1) == 0)
		return ("`>'");
	return (NULL);
}

void	perror_msg_kill_free(char *msg, t_minishell *data)
{
	if (errno && msg)
	{
		kill(data->pid1, SIGUSR1);
		exit(errno);
	}
	else
	{
		kill(data->pid1, SIGUSR1);
		exit(errno);
	}
}

void	print_error_cmd(char *cmd)
{
	ft_putstr_fd(COM, 2);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
}

void	print_error_syntax(char *arg)
{
	ft_putstr_fd(SYNTAX, 2);
	if (arg)
		ft_putstr_fd(get_linker_for_error(arg), 2);
	else
		ft_putstr_fd("`newline'", 2);
	ft_putchar_fd('\n', 2);
}

void	print_error(char *error)
{
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
}

int	print_error_and_failure(char *error)
{
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
	return (FAILURE);
}
