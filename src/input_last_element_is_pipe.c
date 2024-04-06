/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_last_element_is_pipe.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:14:22 by blarger           #+#    #+#             */
/*   Updated: 2024/04/06 17:39:48 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	father_sigint_handler_read_pipe(int sig)
{
	(void)sig;
	//printf("\033[2K\033[1G");
	wait(0);
	printf("ctrl-c pressed in read pipe parent catch\n");
	//printf("\e[32pipe> \e[0m\n");
/* 	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); */
}

void set_father_sigint_action_read_pipe(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &father_sigint_handler_read_pipe;
	sigaction(SIGINT, &act, NULL);
}

static int	read_pipe_input(int pipe_fd[2])
{
	char	*line;

	close(pipe_fd[READ_END]);
	set_child_sigint_action_herefile();
	line = readline("pipe> ");
	if (!line)
	{
		ft_putstr_fd(ENDOFFILE, 2);
		free(line);
		dprintf(2, "\tctr d pressed => exit failure\n");
		exit(EXIT_FAILURE);
	}
	write(pipe_fd[WRITE_END], line, ft_strlen(line));
	free(line);
	close(pipe_fd[WRITE_END]);
	dprintf(2, "\tExit success read pipe input\n");
	exit(EXIT_SUCCESS);
}

static char	*read_child_pipe(pid_t pipe_pid, int pipe_fd[2])
{
	int		status;
	char	*new_content;

	close(pipe_fd[WRITE_END]);
	//set_father_sigint_action_herefile();
	set_father_sigint_action_read_pipe();
	dprintf(2, "parent waiting child\n");
	waitpid(pipe_pid, &status, 0);
	dprintf(2, "parent done waiting child --> WEXITED(status) = %d, WEXITSTATUS(status) = %d\n", WIFEXITED(status), WEXITSTATUS(status));
	//set_child_sigint_action();
	if (WIFEXITED(status) == TRUE)
	{
		if (WEXITSTATUS(status) != 0)
		{
			dprintf(2, "Exit failure detected in father\n");
			close(pipe_fd[READ_END]);
			check_open_fd("read child pipe");
			return (NULL); //ctr-d pressed
		}
		else
		{
			dprintf(2, "Exit success detected in father\n");
			new_content = ft_get_next_line(pipe_fd[READ_END]);
			close(pipe_fd[READ_END]);
			check_open_fd("read child pipe");
			return (new_content);
		}
	}
	else
	{
		dprintf(2, "child process terminated anormally\n");
		return (NULL); //We should never get there
	}
}

static int	handle_pipe_input(t_minishell *data)
{
	pid_t	pipe_pid;
	int		pipe_fd[2];
	char	*new_content;

	if (pipe(pipe_fd) == -1)
	{
		data->last_exit_status = errno;
		perror("Minish: ");
		return (FAILURE); //handle malloc failure
	}
	pipe_pid = fork();
	if (pipe_pid < 0)
		return (FAILURE); //handle failure
	else if (pipe_pid == 0)
		read_pipe_input(pipe_fd);
	else if (pipe_pid > 0)
	{
		new_content = read_child_pipe(pipe_pid, pipe_fd);
		if (!new_content)
			return (FAILURE);//handle failure
		data->prompt = ft_strjoin_free(data->prompt, new_content);
		free(new_content);
	}
	return (SUCCESS);
}

/**
 * @brief Check if the prompt ends with a pipe
 * @return FAILURE if ctr-d is pressed inside pipe prompt
 * 	or if the prompt start by a prompt
 */

int	check_if_last_element_is_pipe(t_minishell *data)
{
	int		i;

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
		return (handle_pipe_input(data));
	check_open_fd("read child pipe");
	return (SUCCESS);
}
