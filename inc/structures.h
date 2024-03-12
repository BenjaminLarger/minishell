/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:30:35 by demre             #+#    #+#             */
/*   Updated: 2024/03/12 09:58:26 by blarger          ###   ########.fr       */
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
	int				n_cmd_args;
}	t_cmd;

typedef struct s_file
{
	int		in_fd;
	int		out_fd;
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

/**
 * @brief Structure representing the shared data and parameters.
 */
typedef struct s_minishell
{
	char	*prompt;
	char	**args;
	int		n_args;
	pid_t	pid1;
	int		is_exit;
	t_file	file;
	t_cmd	*cmds; // prob delete
	int		n_cmds; // prob delete
	char	**linker; // prob delete
	int		n_linker; // prob delete
	int		fd_pipe1[2];
	int		fd_pipe2[2];
	char	*cd_last_dir;
}		t_minishell;

/**
 * @brief Enumerates the type of signals.
 */
enum	e_signal
{
	no_signal,
	ctrlc_signal,
	exit_signal
};

/**
 * @brief Enumerates the type of quotes for tokens.
 */
enum	e_quote
{
	single_quote,
	double_quote
};

/**
 * @brief Structure to hold token-related data when counting number of tokens.
 */
typedef struct s_token_data
{
	int	i;
	int	n_tokens;
	int	is_inside_token;
	int	n_sgl_quotes;
	int	n_dbl_quotes;
}				t_token_data;

/**
 * @brief Structure to hold index-related data during string tokenization.
 */
typedef struct s_index_data
{
	int	i;
	int	j;
	int	start;
	int	n_sgl_quotes;
	int	n_dbl_quotes;
}				t_index_data;

#endif