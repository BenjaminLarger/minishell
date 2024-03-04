/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:00 by demre             #+#    #+#             */
/*   Updated: 2024/03/04 12:18:30 by blarger          ###   ########.fr       */
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

// Signal handling
	//ctrl-c
int		signal_handling(pid_t pid1);
	//ctrl-d
void	set_child_ctr_d_action(void);
char	*ctrl_d_pushed(pid_t pid1);
void	kill_child_process(int sig);

// Shell engine
// shell.c, shell_process_args.c

int		run_shell_loop(t_minishell *data);
int		process_args(t_minishell *data);

// Handle input
// input.c, input_assign_tokens.c, input_count_tokens.c

char	*read_input(char *prompt, pid_t pid1);
int		split_input(t_minishell *data);
int		count_tokens(char const *str);
int		assign_tokens(char **tokens, char const *str);
char	*ctr_d_pushed(pid_t pid1);


// Free arrays
// cleanup_free_arrays.c

void	free_string_array(char **str_array);
void	free_n_string_array(char **str_array, int n);
void	free_array_string_array(char ***array);


#endif