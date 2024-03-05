/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:28:19 by blarger           #+#    #+#             */
/*   Updated: 2024/03/05 11:56:35 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	child(t_minishell *data, int i, int fd[2], char **envp);
static void	sub_parent_process(t_minishell *data, pid_t pid, int pipefd[2]);

void	child_process(t_minishell *data, char **envp, int index)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (free_all(data, PIPE, EXIT_FAILURE));
	pid = fork();
	if (pid < 0)
		return (free_all(data, FORK, EXIT_FAILURE));
	if (pid == 0)
		child(data, index, pipefd, envp);
	else
		sub_parent_process(data, pid, pipefd);
}

static void	child(t_minishell *data, int i, int fd[2], char **envp)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (free_all(data, FORK, EXIT_FAILURE));
	execve(data->args[i]->bash_path , data->args[i], envp);
	return (free_all(data, EXEC_FAIL, EXIT_FAILURE));
}

static void	sub_parent_process(t_minishell *data, pid_t pid, int pipefd[2])
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
	}
	else
		return (free_all(data, WAIT, EXIT_FAILURE));
} */
