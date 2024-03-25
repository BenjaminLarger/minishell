/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redirections_herefile.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:44:46 by blarger           #+#    #+#             */
/*   Updated: 2024/03/25 16:34:05 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_sigint_handler_herefile(int sig)
{
	(void)sig;
	//dprintf(2, "The child_sigint_handler_herefile ID is %d\n", getpid());
	//dprintf(2, "ctrl-c pressed in here file -> EXIT_FAILURE\n"); //
	exit(EXIT_FAILURE);
}

static void	father_sigint_handler_herefile(int sig)
{
	(void)sig;
	printf("ctrl-c pressed in here file parent catch\n"); //
	//free(content);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(EXIT_FAILURE);
}

static void set_child_sigint_action_herefile(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &child_sigint_handler_herefile;
	sigaction(SIGINT, &act, NULL);
}

static void	set_father_sigint_action_herefile(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &father_sigint_handler_herefile;
	sigaction(SIGINT, &act, NULL);
}

static void	write_herefile(t_minishell *data, char	*content)
{
	close(data->file.heredoc_pipe[READ_END]);
	write(data->file.heredoc_pipe[WRITE_END], content, ft_strlen(content));
	close(data->file.heredoc_pipe[WRITE_END]);
	if (data->file.has_infile == TRUE)
	{
		close(data->file.in_fd);
		data->file.has_infile = FALSE;
	}
}

/**
 * @brief Cannot use global variable for to exit the loop, because it doese not
 * exit immediately. We may have to fork the process before creating the pipe,
 * and then handle an instant exit via set_child_sigint_action_herefile
 * setting child_sigint_handler_herefile as exit(EXIT_FAILURE) when reached.
	
 */
static void	read_herefile_util(t_minishell *data, char **args)
{
	char	*line;
	char	*content;
	char	*env_var_replaced;

	dprintf(2, "The child herefile ID is %d\n", getpid());
	set_child_sigint_action_herefile();
	data->file.ctr_d_pressed = false;
	content = ft_calloc(1, sizeof(char));
	if (!content)
		exit(FAILURE); //Handle malloc failure
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			data->file.ctr_d_pressed = true;
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
	env_var_replaced = replace_env_var_in_substr(content, ft_strlen(content));
	if (!env_var_replaced)
		exit(EXIT_FAILURE); // malloc failure
	write_herefile(data, env_var_replaced);
	free(env_var_replaced);
	exit(EXIT_SUCCESS);
}
/**
 * @brief Handle here document using readline. Handle ctr-d ok.
 * //Must implement a siganl management in case of ctr-c
 * 
 * Handle here document using readline. Handle ctr-d quasi ok.
 * 		=> ne marche pas quand on repete plusieurs fois
 * 			d'affile ctr-c dans un herefile.
	
 */

void	read_here_pipe(t_minishell *data, pid_t here_pid)
{
	int	status;

	close(data->file.heredoc_pipe[WRITE_END]);
	dprintf(2, "The parent herefile ID is %d\n", getpid());
	if (!data)
		set_father_sigint_action_herefile();
	dprintf(2, "here father waiting\n");
	waitpid(here_pid, &status, 0);
	set_child_sigint_action();
	dprintf(2, "FATHER can process\n");
	if (WIFEXITED(status))
	{
		data->last_exit_status = WEXITSTATUS(status);
		if (WEXITSTATUS(status) != 0)
		{
			//data->file.has_heredoc = FALSE;
			data->file.has_heredoc = TRUE;
			close(data->file.heredoc_pipe[READ_END]);
			//dprintf(2, "ctr-c pressed, caught in father here fork = %d\n", (WEXITSTATUS(status)));
			//rl_on_new_line();
			//rl_replace_line("", 0);
			//rl_redisplay();
			//data->fd_pipe1[READ_END] = 0;
		}
		else
		{
			data->file.has_heredoc = TRUE;
		}
	}
	if (data->file.has_infile == TRUE)
	{
		close(data->file.in_fd);
		data->file.has_infile = FALSE;
	}
}

int	handle_here_document(t_minishell *data, char **args)
{
	pid_t	here_pid;

	if (!args[1])
	{
		data->last_exit_status = 258;
		return (FAILURE);
	}
	print_array(args);
	
	if (pipe(data->file.heredoc_pipe) == -1)
	{
		data->last_exit_status = errno;
		perror("Minish: ");
		return (FAILURE);
	}
	/* if (data->file.has_heredoc == TRUE)
		close(data->file.heredoc_pipe[READ_END]); */
	here_pid = fork();
	if (here_pid < 0)
		return (FAILURE);
	else if (here_pid == 0)
		read_herefile_util(data, args);
	else
		read_here_pipe(data, here_pid);
	dprintf(2, "HERE SUCCESS\n");
	return (SUCCESS);
}
