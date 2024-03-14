/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:00 by demre             #+#    #+#             */
/*   Updated: 2024/03/14 17:18:09 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
#include <strings.h>
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
extern int	g_last_exit_status;

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

// Shell engine
// shell.c, shell_process_args.c

int		run_shell_loop(t_minishell *data);
int		process_args(t_minishell *data);
int		execute_command(t_minishell *data, int i);

void	exec_args(t_minishell *data);
int		exec_cmd_if_builtin(char **args, int *start);

// Path

int	get_cmd_with_path(char const *cmd, char **cmd_with_path);

// Handle input
// input.c, input_assign_tokens.c, input_count_tokens.c

char	*read_input(char *prompt);
int		split_input_into_args(t_minishell *data);
int		count_tokens(char const *str);
int		assign_tokens(char **tokens, char const *str);

//Process
	//Here_file
void	read_from_input(t_minishell *data);

//Handle environment variable($USER)
void	handle_env_variable(char **args);

//Execute commands
	//BuiltsIn
void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_env(void);
void	builtin_cd(char *arg, t_minishell *data);
void	builtin_export(char **args);
void	builtin_unset(char **args);


//Handle $? last exit command
void	handle_last_exit_status_cmd(char **args);

//Handle redirection
int		handle_redirection(char **args, t_minishell *data);
void	process_input_redirection(char **args, t_minishell *data);

// Free arrays
// cleanup_free_arrays.c
void	free_string_array(char **str_array);
void	free_n_string_array(char **str_array, int n);
void	free_array_string_array(char ***array);

//utils
char	*ft_strjoin_free(char *s1, char *s2);
int		is_linker(char *str);
int		count_commands(char **args);
void	write_fdin_to_fdout(int fd_in, int fd_out);
int		is_string_all_space(char const *str);

//errros_handling.c
char	*get_linker(char *linker);
void	perror_msg_kill_free(char *msg, t_minishell *data);

// Dev functions

void	print_array(char **array);
void	check_open_fd();
void	ft_leaks(void);
void	print_fd(int fd);
void	print_pipes_fd(t_minishell *data);

#endif