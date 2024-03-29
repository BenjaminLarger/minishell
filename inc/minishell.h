/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:00 by demre             #+#    #+#             */
/*   Updated: 2024/03/27 18:01:12 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <strings.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include "libft.h"
# include "errors.h"
# include "structures.h"

# define MAX_PATH_LEN 1024
# define FALSE 0
# define TRUE 1
# define FAILURE 1
# define SUCCESS 0
# define READ_END 0
# define WRITE_END 1

extern int	g_signal;

// Signal handling

void	block_signal(int signal);
void	unblock_signal(int signal);
int		signal_handling(t_minishell *data);

	//ctrl-c
void	set_child_sigint_action(void);
void	set_parent_sigint_action(void);
	//ctrl-d
void	set_child_exit_signal_action(void);
void	set_parent_exit_signal_action(void);

// Initialisation

int		load_env_variables(t_minishell *data, char **envp);
int		init_program(t_minishell *data);

// Shell engine
// shell.c, shell_process_args.c

int		run_shell_loop(t_minishell *data);
int		exec_args(t_minishell *data);
int		get_cmd_without_redirections(t_minishell *data, char ***cmd,
	int start, int end);
//void	exec_command(t_minishell *data, char **cmd);
void	exec_command(t_minishell *data, char **cmd, int end_index);
int		exec_cmd_if_builtin(char **args, t_minishell *data);
int		is_env_changing_builtin(char **cmd, t_minishell *data);

// Path

int		get_cmd_with_path(t_minishell *data, char const *cmd,
	char **cmd_with_path);

// Handle input
// input.c, input_assign_tokens.c, input_count_tokens.c

char	*read_input(char *prompt);
int		split_input_into_args(t_minishell *data);
int		count_tokens(char const *str);
int		assign_tokens(t_minishell *data, char const *str);
int		check_tokens_syntax(char **args);
char	*replace_env_var_in_substr(char const *input, int input_len,
	t_minishell *data);
int		get_ev_str_expanded_len(char const *input, int input_len,
	int *expanded_len, t_minishell *data);
char	*remove_quotes_from_str(char *str);

// Handle input utils

int		is_sgl_linker(char const *str);
int		is_dbl_linker(char const *str);
int		is_outside_quotes(t_token_data *tok);
int		isspace_outside_quotes(int c, t_index_data *ind);
int		islinker_outside_quotes(char const *str, t_index_data *ind);
void	increase_quote_count_if_outside_quotes(char c,
	int *n_sgl_quotes, int *n_dbl_quotes);
int		is_valid_ev_dollar_sign(char c, int *n_sgl_quotes, int *n_dbl_quotes,
	int *first_quote);

//Execute commands
	//BuiltsIn
void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_env(t_minishell *data);
void	builtin_cd(char *arg, t_minishell *data);
void	builtin_export(char **args, t_minishell *data);
void	builtin_unset(char **args);
void	builtin_exit(t_minishell *data);

//Handle redirection

int		handle_redirections_until_next_pipe(t_minishell *data, char **args,
	int start, int end);

// Free arrays
// cleanup_free_arrays.c
void	free_string_array(char **str_array);
void	free_n_string_array(char **str_array, int n);
void	free_int_array(int **int_array, int size);
// void	free_env_array(void);

//utils
char	*ft_strjoin_free(char *s1, char *s2);
int		is_linker(char *str);
int		is_redirection(char *str);
int		count_commands(char **args);
void	write_fdin_to_fdout(int fd_in, int fd_out);
int		is_string_all_space(char const *str);
int		command_with_pipe(char **args);
int		is_valid_ev_character(char c);
void	check_and_replace_last_exit_status_call(char **args, t_minishell *data);
int		handle_here_document(t_minishell *data, char **args);
char	*ft_getenv(t_minishell *data, char *key);

//errros_handling.c

char	*get_linker_for_error(char *linker);
void	perror_msg_kill_free(char *msg, t_minishell *data);
void	print_error_cmd(char *cmd);
void	print_error_syntax(char *arg);
void	print_error(char *error);
int		print_error_and_failure(char *error);

// Dev functions

void	print_array(char **array, char *message);
void	check_open_fd(char *message);
void	ft_leaks(void);
void	print_fd(int fd);
void	print_pipes_fd(t_minishell *data);
void	print_files_fd(t_minishell *data);
void	print_pipe_contents(int pipefd);

#endif