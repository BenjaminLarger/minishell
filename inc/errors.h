/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:07 by demre             #+#    #+#             */
/*   Updated: 2024/04/04 13:21:20 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//This file aim to print error message when needed
//Use case example : if (!) => print_error(MALLOC_FAIL)
//I made a copy of the same file I have used in my pipex project => this is a draft
# define MALLOC_FAIL	"Malloc allocation failed.\n"
# define ARG			"The input must have one parameters.\n"
# define OPEN_PIPE		"Error opening pipe."
# define FORK			"Fork failed to be created.\n"
# define DUP2			"dup2 failed to create the duplication.\n"
# define EXEC_FAIL		"sh: command not found: "
# define ENV			"Can't find the environment"
# define COM			"minish: command not found: "
# define FILE			"No such file or directory \n"
# define PIPE			"Pipe creation failed."
# define WAIT			"waitpid function failed to resume parent process.\n"
# define CHILD			"Child process terminated abnormally\n"
# define PERM			"minish: permission denied: "
# define BASH			"minish: "
# define SYNTAX			"minish: syntax error near unexpected token `"
# define IDENTIFIER		"minish: export: not a valid identifier: `"

#endif