/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:00 by demre             #+#    #+#             */
/*   Updated: 2024/03/06 15:17:38 by demre            ###   ########.fr       */
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

extern int g_signal;

// Signal handling

void	block_signal(int signal);
void	unblock_signal(int signal);
int		signal_handling(t_minishell *data, int *status);

	//ctrl-c
void	set_child_sigint_action(void);
void	set_parent_sigint_action(void);
	//ctrl-d
void	set_parent_exit_signal_action(t_minishell *data);

// Shell engine
// shell.c, shell_process_args.c, shell_split_args.c

int		run_shell_loop(t_minishell *data);
int		process_args(t_minishell *data);
int		split_args_into_cmds(t_minishell *data);

// Handle input
// input.c, input_assign_tokens.c, input_count_tokens.c

char	*read_input(char *prompt);
int		split_input_into_args(t_minishell *data);
int		count_tokens(char const *str);
int		assign_tokens(char **tokens, char const *str);

//Process
	//Here_file
void	process_here_file(t_minishell *data, int n_cmds);

//BuiltsIn
void	builtin_echo(char **args, int n_cmd);
void	builtin_pwd(void);
void	builtin_env(void);
void	builtin_cd(char *arg);

// Free arrays
// cleanup_free_arrays.c

void	free_string_array(char **str_array);
void	free_n_string_array(char **str_array, int n);
void	free_array_string_array(char ***array);

//utils
char	*ft_strjoin_free(char *s1, char *s2);

// Dev functions

void	print_array(char **array);

#endif