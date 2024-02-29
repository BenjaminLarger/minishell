/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:30:35 by demre             #+#    #+#             */
/*   Updated: 2024/02/29 16:30:56 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <stdbool.h>

//This file aims to stock structures used in minishell project
//I made a copy of the same file I have used in my pipex project => this is a draft
typedef struct s_cmd
{
	char			**cmd;
	bool			valid_cmd;
	char			*bash_path;
	int				n_cmd;
}	t_cmd;

typedef struct s_file
{
	int		fd1;
	int		fd2;
	int		fd1_limited;
	char	*filename1;
	char	*filename2;
	char	*filename_limited;
	char	*limited;
	bool	exist_file_1;
	bool	read_access_1;
	bool	write_access_2;
}	t_file;

typedef struct s_pipex
{
	t_file	*file;
	t_cmd	*cmds;
	int		total_cmd;
	int		pipefd[2];
	pid_t	child_pid;
	int		fd_child;
	int		fd_father;
	char	**env;
}	t_pipex;

#endif