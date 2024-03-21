/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:30:35 by demre             #+#    #+#             */
/*   Updated: 2024/03/21 18:42:56 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <stdbool.h>

typedef struct s_file
{
	int		exit_status;
	int		in_fd;
	int		out_fd;
	int		heredoc_pipe[2];
	int		has_infile;
	int		has_outfile;
	int		has_heredoc;
	bool 	ctr_d_pressed;
	int		fd1_limited;
	char	*filename1;
	char	*filename2;
	char	*filename_limited;
	char	*limited;
	bool	exist_file_1;
	bool	read_access_1;
	bool	write_access_2;
}	t_file;

/**
 * @brief Structure representing the shared data and parameters.
 */
typedef struct s_minishell
{
	char	*prompt;
	char	**args;
	bool	args_to_free; //prob delete
	int		n_args;
	pid_t	pid1;
	int		is_exit;
	t_file	file;
	int		n_cmds; // prob delete
	char	**linker; // prob delete
	int		n_linker; // prob delete
	int		save_stdin_fd;
	int		fd_pipe1[2];
	int		fd_pipe2[2];
	char	*cd_last_dir;
	int		executed_command;
	int		last_exit_status;
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
