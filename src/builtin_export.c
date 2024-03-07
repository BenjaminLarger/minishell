/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:34:57 by blarger           #+#    #+#             */
/*   Updated: 2024/03/07 14:13:36 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SEPARATOR "="

static void	display_exported_variable(void);
static void define_env_variable(char *arg);
static int	count_sep(char *arg);

/* TO IMPLEMENT
-> Without any arguments, the command will generate or display all
	exported variables. 

You can also assign a value before exporting a function as shown
-> export name[=value]
-> export students
 */

/* IMPORTANT
We should be able to set as many env variable as there are cmds (ex: export name_1=value_1 ...  name_n=value_n) */

/* HEDGE CASES
if there is no '=' (the SEPARATOR), we do nothing */

/* void	builtin_export(char **args, t_minishell *data)
{
	int	i;

	i = 1;
	if (!arg) //remove data
		return (display_exported_variable());
	else
	{
		while (i < data->n_cmd)
		{
			define_env_variable(arg);
			i++;
		}
	}
} */

void	builtin_export(char *arg, t_minishell *data)
{
	int	i;

	i = 1;
	if (!arg && data) //remove data
		return (display_exported_variable());
	else
		define_env_variable(arg);
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

static void define_env_variable(char *arg)
{
	char	*arg_token;
	char	*name;
	char	*value;
	int		total_sep;

	total_sep = count_sep(arg);
	if (total_sep == 0)
		return ;
	arg_token = strtok(arg, SEPARATOR); //malloc ? Nothing in the man
	name = ft_strdup(arg_token); //to free
	printf("name = %s\n", name);
	value = (char *)ft_calloc(sizeof(char), 1); //malloc
	if (!value)
		return ; //Handle malloc fail
	while (total_sep > 0)
	{
		arg_token = strtok(NULL, SEPARATOR);
		value = ft_strjoin_free(value, arg_token); //to free
		value = ft_strjoin_free(value, "=");
		printf("value = %s\n", value);
		total_sep--;
	}
	value[ft_strlen(value) - 1] = '\0';
	printf("value = %s\n", value);
/* 	if (name && value)
		get_env(); */
}

static int	count_sep(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == SEPARATOR[0])
			count++;
		i++;
	}
	printf("count = %d\n", count);
	return (count);
}