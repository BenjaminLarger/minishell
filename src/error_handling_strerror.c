/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_generic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:58:59 by blarger           #+#    #+#             */
/*   Updated: 2024/04/10 16:34:51 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
