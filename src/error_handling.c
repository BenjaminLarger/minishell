/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:58:59 by blarger           #+#    #+#             */
/*   Updated: 2024/04/09 17:15:44 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr_fd(arg, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

int	print_error_and_failure(char *error)
{
	ft_putstr_fd(error, 2);
	return (FAILURE);
}

void	print_error(char *error)
{
	ft_putstr_fd(error, 2);
}

void	print_strerror_and_arg(char *arg)
{
	ft_putstr_fd("minish: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
}

int	print_strerror_and_set_exit_status_and_failure(t_minishell *data)
{
	ft_putstr_fd("minish: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	data->last_exit_status = 1;
	return (FAILURE);
}

void	print_strerror_and_set_exit_status(t_minishell *data)
{
	ft_putstr_fd("minish: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	data->last_exit_status = 1;
}

void	print_error_message_and_arg(char *error, char *arg)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("'\n", 2);
}
