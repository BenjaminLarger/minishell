/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:00 by demre             #+#    #+#             */
/*   Updated: 2024/03/12 12:03:48 by blarger          ###   ########.fr       */
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
void	set_parent_exit_signal_action(void);

// Shell engine
// shell.c, shell_process_args.c, shell_split_args.c

int		run_shell_loop(t_minishell *data);
int		process_args(t_minishell *data);
int		execute_command(t_minishell *data, int i);
int		split_args_into_cmds(t_minishell *data);

void	exec_args(t_minishell *data);

// Path

int	get_paths(char ***paths);

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
int		count_arg_after_cmd(char **args);

//errros_handling.c
char	*get_linker(char *linker);
void	msg_kill_free(char *m, char *s, int ex, t_minishell *d);

// Dev functions

void	print_array(char **array);
void	print_all_cmds_and_linkers(t_minishell *data);
void	ft_leaks(void);

#endif