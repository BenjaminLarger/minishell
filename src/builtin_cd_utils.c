/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:12 by blarger           #+#    #+#             */
/*   Updated: 2024/04/10 13:58:20 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_cd(char *arg, t_minishell *data, char *error_msg)
{
	ft_putstr_fd("minish: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd(error_msg, 2);
	data->last_exit_status = 1;
}

int	return_true_or_false_set_exit_status(int ret, int sta, t_minishell *d)
{
	d->last_exit_status = sta;
	return (ret);
}
