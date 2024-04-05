/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:57:45 by blarger           #+#    #+#             */
/*   Updated: 2024/04/05 16:58:11 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_extrem_value(char *str, int len)
{
	int		last_digit;
	int		nb_without_last_digit;
	char	copy[12];

	last_digit = 0;
	printf ("len = %d\n", len);
	if (len < 10 || (len < 11 && (str[0] == '-' || str[0] == '+')))
		return (FALSE);
	else if ((len > 10 && (str[0] != '-' && str[0] != '+')) || (len > 11))
		return (TRUE);
	ft_strlcpy(copy, str, len);
	nb_without_last_digit = ft_atoi(copy);
	last_digit = str[ft_strlen(str) - 1] - '0';
	if (nb_without_last_digit > 0
		&& (2147483647 - (nb_without_last_digit * 10) - last_digit) < 0)
		return (TRUE);
	else if (nb_without_last_digit < 0
		&& (-2147483648 + (nb_without_last_digit * 10) + last_digit) > 0)
		return (TRUE);
	return (FALSE);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (FALSE);
		i++;
	}
	if (is_extrem_value(str, i) == TRUE)
		return (FALSE);
	else
		return (TRUE);
}

void	builtin_exit(t_minishell *data, char **args)
{
	ft_putstr_fd("exit\n", 2);
	if (command_with_pipe(data->args) == TRUE)
		return ;
	data->is_exit = TRUE;
	if (args[1] && is_numeric(args[1]) == FALSE)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minish: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->is_exit = TRUE;
		data->last_exit_status = 255;
	}
	else if (args[1] && is_numeric(args[1]) == TRUE && args[2] != NULL)
	{
		ft_putstr_fd("exit\nminish: exit: too many arguments\n", 2);
		data->last_exit_status = 1;
		data->is_exit = FALSE;
		return ;
	}
	if (args[1] && is_numeric(args[1]) == TRUE)
		data->last_exit_status = ft_atoi(args[1]);
	else
		data->last_exit_status = 255;
}
