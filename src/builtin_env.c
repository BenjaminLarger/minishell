/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:19:52 by blarger           #+#    #+#             */
/*   Updated: 2024/04/05 14:18:20 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_minishell *data)
{
	int	i;

	i = 0;
	while (data->env_msh[i])
	{
		printf("%s\n", data->env_msh[i]);
		i++;
	}
}
