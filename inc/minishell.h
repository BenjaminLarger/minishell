/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:00 by demre             #+#    #+#             */
/*   Updated: 2024/03/05 15:03:09 by demre            ###   ########.fr       */
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

	//ctrl-c
int		signal_handling(t_minishell *data, int *status);
void	set_child_sigint_action(void);
void	set_parent_sigint_action(void);
	//ctrl-d
void	set_parent_exit_signal_action(t_minishell *data);

// Shell engine
// shell.c, shell_process_args.c

int		run_shell_loop(t_minishell *data);
int		process_args(t_minishell *data);

// Handle input
// input.c, input_assign_tokens.c, input_count_tokens.c

char	*read_input(char *prompt);
int		split_input_in_args(t_minishell *data);
int		count_tokens(char const *str);
int		assign_tokens(char **tokens, char const *str);


// Free arrays
// cleanup_free_arrays.c

void	free_string_array(char **str_array);
void	free_n_string_array(char **str_array, int n);
void	free_array_string_array(char ***array);


#endif