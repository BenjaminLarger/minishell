/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:18:07 by demre             #+#    #+#             */
/*   Updated: 2024/04/10 16:55:22 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC_FAIL	"minish: memory allocation failed.\n"
# define ARG			"The input must have one parameters.\n"
# define DUP2			"dup2 failed to create the duplication.\n"
# define ENV			"Can't find the environment"
# define COM			"minish: command not found: "
# define FILE			"No such file or directory \n"
# define WAIT			"waitpid function failed to resume parent process.\n"
# define CHILD			"Child process terminated abnormally\n"
# define PERM			"minish: permission denied: "
# define BASH			"minish: "
# define SYNTAX			"minish: syntax error near unexpected token `"
# define SYNTAXPIPE		"minish: syntax error near unexpected token `|'\n"
# define IDENTIFIER		"minish: export: not a valid identifier: `"
# define ENDOFFILE		"minish: syntax error: unexpected end of file\n"
# define PIPE			"minish: Pipe failed to be created\n"

#endif