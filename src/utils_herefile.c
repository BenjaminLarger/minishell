/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_herefile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:44:46 by blarger           #+#    #+#             */
/*   Updated: 2024/03/21 18:05:42 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_herefile(t_minishell *data, char	*content, bool ctr_d)
{
	data->file.has_heredoc = TRUE;
	if (ctr_d == false)
		write(data->file.heredoc_pipe[WRITE_END], content, ft_strlen(content));
	close(data->file.heredoc_pipe[WRITE_END]);
	free(content);
}

static void	read_herefile_util(t_minishell *data, char **args, char	*content)
{
	char	*line;
	bool 	ctr_d_pressed;

	ctr_d_pressed = false;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ctr_d_pressed = true;
			free(line);
			break ;
		}
		if (!ft_strcmp(line, args[1]))
		{
			free(line);
			break ;
		}
		content = ft_strjoin_free(content, line);
		content = ft_strjoin_free(content, "\n");
		free(line);
	}
	if (ctr_d_pressed == false)
		write_herefile(data, content, ctr_d_pressed);
}
/**
 * @brief Handle here document using readline. Handle ctr-d ok.
 * //Must implement a siganl management in case of ctr-c
 * 
 * => Must act like that : 
 * bash-3.2$ << wswd
	> <ctr-c>
	bash-3.2$
	
 */
int	handle_here_document(t_minishell *data, char **args)
{
	char	*content;

	content = ft_calloc(1, sizeof(char));
	if (!content)
		return (FAILURE); //Handle malloc failure
	print_array(args);
	if (is_linker(args[1]) == TRUE)
		perror_msg_kill_free(SYNTAX, data);
	if (data->file.has_heredoc == TRUE)
		close(data->file.heredoc_pipe[READ_END]);
	if (pipe(data->file.heredoc_pipe) == -1)
	{
		data->last_exit_status = errno;
		perror("Minish: ");
		return (FAILURE);
	}
	//set_parent_sigint_action_for_herefile();
	read_herefile_util(data, args, content);
	if (data->file.has_infile == TRUE)
	{
		close(data->file.in_fd);
		data->file.has_infile = FALSE;
	}
	//set_parent_sigint_action();
	return (SUCCESS);
}
