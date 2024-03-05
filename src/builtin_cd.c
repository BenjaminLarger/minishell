/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:15:50 by blarger           #+#    #+#             */
/*   Updated: 2024/03/05 16:44:58 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FUNCTIONS
/* The readdir() function shall return a pointer to a structure representing 
the directory entry at the current position in the directory stream specified
by the argument dirp, and position the directory stream at the next entry. */

//IMPORTANT
/* After a call to fork(), either the parent or child (but not both) may continue processing
the directory stream using readdir(), rewinddir(), [XSI] [Option Start]  or seekdir().
[Option End] If both the parent and child processes use these functions, the result is undefined. */

//HOW DOES IT WORK ?
/* DIR *dirp: This is a pointer to a directory stream, which is typically obtained by opening
a directory using the opendir function. */


void	echo_builtin(t_minishell *data)
{
	DIR				*dir;
	struct dirent	*dp;

	dir = opendir(".");
	if (!dir)
		perror("Cannot open .");
}
