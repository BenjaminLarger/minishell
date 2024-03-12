/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_here_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:11:57 by blarger           #+#    #+#             */
/*   Updated: 2024/03/12 11:09:46 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	write_to_in_fd(t_minishell *data);

void	read_from_input(t_minishell *data)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read)
	{
		buffer = ft_get_next_line(STDIN_FILENO);
		data->file.limited = ft_strjoin_free(data->file.limited, buffer);
		free(buffer);
		if (ft_strstr(data->file.limited, data->args[2]))
			break ;
	}
	write_to_in_fd(data);
}

static void	write_to_in_fd(t_minishell *data)
{
	int		i;
	int		limit_len;

	limit_len = ft_strlen(data->args[1]);
	i = 0;
	while (i < ft_strlen(data->file.limited))
		i++;
	while (limit_len >= 0)
	{
		data->file.limited[--i] = '\0';
		limit_len--;
	}
	write(pipefd[1], data->file.limited,
		ft_strlen(data->file.limited));
	close(data->file.in_fd);
	open(data->file.filename1, O_RDONLY);
	free(data->file.limited);
} */
