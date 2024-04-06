/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_last_element_is_pipe.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:14:22 by blarger           #+#    #+#             */
/*   Updated: 2024/04/06 13:09:45 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_pipe_input(void)
{
	char	*line;

	line = readline("pipe> ");
	if (!line)
	{
		ft_putstr_fd(ENDOFFILE, 2);
		return (NULL);
	}
	else
		return (line);
}

/**
 * @brief Check if the prompt ends with a pipe
 * @return FAILURE if ctr-d is pressed inside pipe prompt
 * 	or if the prompt start by a prompt
 */

int	check_if_last_element_is_pipe(t_minishell *data)
{
	int		i;
	char	*new_content;

	i = 0;
	while (data->prompt[i] == ' ')
		i++;
	if (data->prompt[i] == '|')
	{
		ft_putstr_fd(SYNTAXPIPE, 2);
		return (FAILURE);
	}
	while (data->prompt[i])
		i++;
	i--;
	while (data->prompt[i] == ' ')
		i--;
	if (data->prompt[i] == '|')
	{
		new_content = read_pipe_input();
		if (!new_content)
			return (FAILURE);
		data->prompt = ft_strjoin_free(data->prompt, new_content);
		free(new_content);
	}
	return (SUCCESS);
}
