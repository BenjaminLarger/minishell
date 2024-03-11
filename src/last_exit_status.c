/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:43:00 by blarger           #+#    #+#             */
/*   Updated: 2024/03/11 10:56:13 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* HOW DOES IT WORK ?
$? means the last exit status in bash.
To retrieve it, we nee a global variable that is updated each time there is an exit.
=> g_last_exit_status = WEXITSTATUS(status);
We have to implement it for each exit on each pipes,
keeping track of the waitpid return, as I have done in the main function.
Implementation unfinished. */

void	handle_last_exit_status_cmd(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1] == '?' && args[i][2] == '\0')
		{
			args[i] = ft_itoa(g_last_exit_status);
		}
		i++;
	}
}
