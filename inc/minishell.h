/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:00 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 14:50:44 by blarger          ###   ########.fr       */
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
void	set_child_sigint_action_during_prompt(void);
void	set_parent_sigint_action(void);
	//ctrl-d
void	set_parent_exit_signal_action(void);
	//ctr- \						//
void	set_child_sigquit_action_during_prompt(void);
void	set_child_sigquit_action_after_prompt(void);

// Initialisation

int		load_env_variables(t_minishell *data, char **envp);
int		init_program(t_minishell *data);

// Shell engine
// shell.c, shell_process_args.c

int		run_shell_loop(t_minishell *data);
int		exec_args(t_minishell *data);
int		get_cmd_without_redirections(t_minishell *data, char ***cmd,
	int start, int end);
void	exec_command_with_pipe(t_minishell *data, char **cmd);
void	exec_command_nopipe(t_minishell *data, char **cmd);
int		exec_cmd_if_builtin(char **args, t_minishell *data);
int		is_env_changing_builtin(char **cmd, t_minishell *data);

// Path

int		get_cmd_with_path(t_minishell *data, char const *cmd,
	char **cmd_with_path);

// Handle input

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
int		check_if_last_element_is_pipe(t_minishell *data);


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
void	builtin_pwd(t_minishell *data);
void	builtin_env(t_minishell *data);
void	builtin_cd(char *arg, t_minishell *data);
void	builtin_export(char **args, t_minishell *data);
void	builtin_unset(char **args, t_minishell *data);
void	builtin_exit(t_minishell *data, char **args);

	//builtin_export_update

int		new_shell_var(char ***env_msh, char *new_var);
int		replace_shell_var(char ***env_msh, char *new_var, int end);
int		new_shell_var_without_plus(char ***env_msh, char *new_var, int end);
int		append_shell_var(char ***env_msh, char *new_var, int end);

//Handle redirection

int		handle_redirections(t_minishell *data, char **args, int start, int end);

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
void	set_child_sigint_action_herefile(void);
void 	set_child_sigint_action_after_prompt(void);
void	set_father_sigint_action_herefile(void);
char	*ft_getenv(t_minishell *data, char *key);
void	print_error_cd(char *arg, t_minishell *data, char *error_msg);
void	export_pwd_or_old_pwd(t_minishell *data, char *dir, char *pwd);
int		return_true_or_false_set_exit_status(int ret, int sta, t_minishell *d);
int		is_valid_shell_value(char *arg, t_minishell *data);
int		is_valid_value_character(char c);

//errros_handling.c

//char	*get_linker_for_error(char *linker);
void	perror_msg_kill_free(char *msg, t_minishell *data);
void	print_error_cmd(char *cmd);
void	print_error_syntax(char *arg);
int		print_error_and_failure(char *error);
void	print_error(char *error);
void	print_strerror_and_arg(char *arg);
void	print_error_message_and_arg(char *error, char *arg);
int		print_strerror_and_set_exit_status_and_failure(t_minishell *data);
void	print_strerror_and_set_exit_status(t_minishell *data);

// Dev functions

void	print_array(char **array, char *message);
void	check_open_fd(char *message);
void	ft_leaks(void);
void	print_fd(int fd);
void	print_pipes_fd(t_minishell *data);
void	print_files_fd(t_minishell *data);
void	print_pipe_contents(int pipefd);

#endif