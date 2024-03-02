/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:00 by demre             #+#    #+#             */
/*   Updated: 2024/03/02 15:06:45 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
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


typedef struct s_index_data
{
	int	i;
	int	j;
	int	start;
	int	n_sgl_quotes;
	int	n_dbl_quotes;
}				t_index_data;

typedef struct s_word_data
{
	int	i;
	int	n_words;
	int	inside_word;
	int	n_sgl_quotes;
	int	n_dbl_quotes;
}				t_word_data;


// 1_read_input.c //

char	*read_input(char *prompt);

// Handle prompt

int		handle_prompt(char **prompt);
int		process_input(char **prompt);
int		count_tokens(char *str);
char	**assign_tokens(char **tokens, char *str);

// Free arrays

void	free_string_array(char **str_array);
void	free_n_string_array(char **str_array, int n);
void	free_array_string_array(char ***array);


#endif