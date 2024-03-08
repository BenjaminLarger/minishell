/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:34:57 by blarger           #+#    #+#             */
/*   Updated: 2024/03/08 13:51:20 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SEPARATOR "="

static void	display_exported_variable(void);
static void	define_env_variable(char *arg);
static int	count_value_len(char *arg);

/* TO IMPLEMENT
-> Without any arguments, the command will generate or display all
	exported variables. 

You can also assign a value before exporting a function as shown
-> export name[=value]
-> export students
 */

/* IMPORTANT
We should be able to set as many env variable as there are cmds
(ex: export name_1=value_1 ...  name_n=value_n) */

/* FUNCTIONS
The setenv() function adds the variable name to the environment
       with the value value, if name does not already exist.  If name
       does exist in the environment, then its value is changed to value
       if overwrite is nonzero; if overwrite is zero, then the value of
       name is not changed */

/* HEDGE CASES
if there is no '=' (the SEPARATOR), we do nothing */

void	builtin_export(char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		return (display_exported_variable());
	else
	{
		while (args[i])
		{
			define_env_variable(args[i]);
			i++;
		}
	}
}

static void	display_exported_variable(void)
{
	extern char	**environ;
	char		**s;

	s = environ;
	while (*s)
	{
		printf("declare -x %s\n", *s);
		s++;
	}
}

static void	define_env_variable(char *arg)
{
	char	*name;
	char	*value;
	int		len;

	len = count_value_len(arg);
	if (len == 0)
		return ;
	value = ft_strchr(arg, '=');
	value++;
	name = strtok(arg, SEPARATOR);
	setenv(name, value, 1);
}

static int	count_value_len(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i] && arg[i] != SEPARATOR[0])
		i++;
	while (arg[i])
	{
		count++;
		i++;
	}
	return (count);
}
