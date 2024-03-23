/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:30:35 by demre             #+#    #+#             */
/*   Updated: 2024/03/23 16:34:11 by demre            ###   ########.fr       */
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
 * @brief Enumerates the type of quotes.
 */
enum	e_quote_type
{
	no_quote,
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

/**
 * @brief Structure to hold data during the calculation of the length of the
 * expanded string before replacing the environment variables.
 */
typedef struct s_expanded_data
{
	char	*temp_ev_name;
	int		expanded_len;
	int		ev_start;
	int		n_sgl_quotes;
	int		n_dbl_quotes;
	int		first_quote;
}				t_expanded_data;

typedef struct s_replace_ev_data
{
	char	*expanded;
	int		expanded_len;
	int		exp_idx;
	char	*temp_ev_value;
	char	*temp_ev_name;
	int		ev_start;
	int		n_sgl_quotes;
	int		n_dbl_quotes;
	int		first_quote;
}				t_replace_ev_data;

#endif
