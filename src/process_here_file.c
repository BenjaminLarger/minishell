/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_here_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:11:57 by blarger           #+#    #+#             */
/*   Updated: 2024/03/05 16:44:58 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_from_input(t_minishell *data);
static void	open_here_files(t_minishell *data, int n_cmds);
static void	read_from_input(t_minishell *data);
static void	write_to_fd1(t_minishell *data);

void	process_here_file(t_minishell *data, int n_cmds)
{
	int		i;
	char	*envp;

	envp = getenv("PATH");
	i = -1;
	open_here_files(data, n_cmds);
	read_from_input(data);
	/* dup2(data->file.fd1, STDIN_FILENO);
	while (++i < n_cmds - 1)
	{
		if (i == 0)
			child_process(data, envp, 0);
		else
			child_process(data, envp, i + 1);
	}
	dup2(data->file.fd2, STDOUT_FILENO);
	execve(data->args[n_cmds - 1].bash_path, data->args[n_cmds - 1],envp); */
}

static void	open_here_files(t_minishell *data, int n_cmds)
{
	data->file.filename1 = ft_strdup("here_file"); //to free
	data->file.filename2 = ft_strdup(data->args[n_cmds + 2]); //to free
	data->file.fd1 = open (data->file.filename1, O_CREAT
			| O_RDWR | O_TRUNC, 0644); //Here we must not create a file. Or make it invisble
	data->file.fd2 = open(data->args[n_cmds + 2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!data->file.filename1 || !data->file.filename2)
		return (free_all(data, MALLOC_FAIL, EXIT_FAILURE));
}

static void	read_from_input(t_minishell *data)
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
	write_to_fd1(data);
}

static void	write_to_fd1(t_minishell *data)
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
	write(data->file.fd1, data->file.limited,
		ft_strlen(data->file.limited));
	close(data->file.fd1);
	open(data->file.filename1, O_RDONLY);
	free(data->file.limited);
}
