/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:19:52 by blarger           #+#    #+#             */
/*   Updated: 2024/03/25 20:38:00 by demre            ###   ########.fr       */
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
