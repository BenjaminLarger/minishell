/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:34:57 by blarger           #+#    #+#             */
/*   Updated: 2024/04/05 13:18:22 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_exported_variable(t_minishell *data)
{
	int	i;
	
	i = 0;
	while (data->env_msh[i])
	{
		printf("declare -x %s\n", data->env_msh[i]);
		i++;
	}
}

static int	is_valid_shell_var(char *arg)
{
	int	i;

	i = 0;
	dprintf(2, "is_valid_shell_var arg: %s\n", arg); //
	while (arg[i] && is_valid_ev_character(arg[i]) == TRUE)
		i++;
	if (i != 0 && ((arg[i] && arg[i] == '=')
		|| (arg[i] && arg[i] == '+' && arg[i + 1] && arg[i + 1] == '=')))
	{
		dprintf(2, "IS VALID\n"); //
		return (TRUE);
	}
	else if (arg[i] && is_valid_ev_character(arg[i]) == FALSE)
	{
		dprintf(2, "IS not VALID\n"); //
		print_error_message_and_arg(IDENTIFIER, arg);
		return (FALSE);
	}
	else
	{
		dprintf(2, "IS not VALID\n"); //
		return (FALSE);
	}
}

static void	new_shell_var_or_replace(char ***env_msh, char *new_var, int end)
{
	int		i;
	int		old_size;
	char	**temp_env;

	i = 0;
	while ((*env_msh)[i])
	{
		if (ft_memcmp((*env_msh)[i], new_var, end) == 0
			&& (*env_msh)[i][end] == '=')
		{
dprintf(2, "new_shell_var_or_replace ALREADY EXISTS\n"); //
dprintf(2, "(*env_msh)[i]: %s, new_var: %s\n", (*env_msh)[i], new_var); //
			free((*env_msh)[i]);
			(*env_msh)[i] = ft_strdup(new_var);
			if (!(*env_msh)[i])
				return ; // Malloc failed
			return ; // success
		}
		i++;
	}

	temp_env = *env_msh;
	old_size = 0;
	while (temp_env[old_size])
		old_size++;
dprintf(2, "old_size: %d\n", old_size); //
	*env_msh = (char **)malloc((old_size + 2) * sizeof(char *));
	if (!(*env_msh))
		return ; // Malloc failed
	ft_memcpy(*env_msh, temp_env, old_size * sizeof(char *)); // char ** ?
	(*env_msh)[old_size] = ft_strdup(new_var);
	if (!(*env_msh)[old_size])
		return ; // Malloc failed
	(*env_msh)[old_size + 1] = NULL;
	free(temp_env);
}

static void	new_shell_var_without_plus(char ***env_msh, char *new_var, int end)
{
	int		old_size;
	char	**temp_env;
//	int		i;
	int		len_new_var;

	temp_env = *env_msh;
	old_size = 0;
	while (temp_env[old_size])
		old_size++;
dprintf(2, "old_size: %d, end: %d, ft_strlen(new_var): %d\n", old_size, end, ft_strlen(new_var)); //
	*env_msh = (char **)malloc((old_size + 2) * sizeof(char *));
	if (!(*env_msh))
		return ; // Malloc failed
	ft_memcpy(*env_msh, temp_env, old_size * sizeof(char *)); // char ** ?
	
	len_new_var = ft_strlen(new_var);
	(*env_msh)[old_size] = (char *)malloc(len_new_var * sizeof(char));
	if (!(*env_msh)[old_size])
		return ; // Malloc failed
	ft_memcpy((*env_msh)[old_size], new_var, end);
	(*env_msh)[old_size][end] = '=';
dprintf(2, "*(new_var + end + 1): %c\n", *(new_var + end + 1)); //
	ft_memcpy((*env_msh)[old_size] + end + 1, new_var + end + 2, len_new_var - end + 2);
dprintf(2, "*(new_var + end + 1): %c\n", *(new_var + end + 1)); //
	(*env_msh)[old_size][end + 1 + (3)] = '\0';
	
	(*env_msh)[old_size + 1] = NULL;
dprintf(2, "new_shell_var_without_plus (*env_msh)[old_size]: %s\n", (*env_msh)[old_size]); //
	free(temp_env);
}

static void	add_to_shell_var_or_new(char ***env_msh, char *new_var, int end)
{
	int		i;
	int		size;

	i = 0;
	dprintf(2, "update_shell_var new_var: %s, new_var[%d]: %c\n", new_var, end, new_var[end]); //
	while ((*env_msh)[i])
	{
		if (ft_memcmp((*env_msh)[i], new_var, end) == 0
			&& (*env_msh)[i][end] == '=')
		{
			printf("Match found at index %d\n", i);
			printf("(*env_msh)[%d][%d]: %c\n", i, end, (*env_msh)[i][end]);
			printf("(*env_msh)[i]: %s matches with %s from 0 to %d\n", (*env_msh)[i], new_var, end);
			printf("ft_strchr(new_var, '='): %s\n", ft_strchr(new_var, '=') + 1);
			printf("ft_strlen((*env_msh)[i]): %d, ft_strlen(ft_strchr(new_var, '=') + 1): %d\n", ft_strlen((*env_msh)[i]), ft_strlen(ft_strchr(new_var, '=') + 1));
			
			(*env_msh)[i] = ft_strjoin_free((*env_msh)[i],
				ft_strchr(new_var, '=') + 1);
			if (!(*env_msh)[i])
				return ; // Malloc failed
			break ;
		}
		i++;
	}

printf("new (*env_msh)[i]: %s\n", (*env_msh)[i]);
	size = 0;
	while ((*env_msh)[size])
		size++;
dprintf(2, "end add_to_shell_var_or_new i: %d, size: %d\n", i, size); //
	if (i == size)
		new_shell_var_without_plus(env_msh, new_var, end);
}

static int	handle_shell_var(char ***env_msh, char *new_var)
{
	int		i;

	i = 0;
	while (new_var[i] && is_valid_ev_character(new_var[i]) == TRUE)
		i++;
	if (new_var[i] && new_var[i] == '=')
		new_shell_var_or_replace(env_msh, new_var, i);
	else if (new_var[i] && new_var[i] == '+'
		&& new_var[i + 1] && new_var[i + 1] == '=')
		add_to_shell_var_or_new(env_msh, new_var, i);
	if (!(*env_msh))
		return (FAILURE);
	dprintf(2, "SUCCESS\n"); //
	return (SUCCESS);
}

void	builtin_export(char **args, t_minishell *data)
{
	int		i;

	i = 1;

	print_array(args, "builtin_export"); //
	int size = 0; //
	while (data->env_msh[size]) //
		size++; //
	dprintf(2, "data->env_msh[size] before: %d\n", size); //

	if (!args[1])
		return (display_exported_variable(data));
	else if (command_with_pipe(data->args) == TRUE)
		return ;
	else
	{
		while (args[i])
		{
			if (is_valid_shell_var(args[i]) == TRUE)
			{
			//	data->env_msh = concat_and_add_env(data->env_msh, args[i]);
				handle_shell_var(&data->env_msh, args[i]);
			//	if (handle_shell_var(data->env_msh, args[i]) == FAILURE)
			//		return (FAILURE); // Handle malloc failure
			}
			i++;
		}
	}
	size = 0; //
	while (data->env_msh[size]) //
		size++; //
	dprintf(2, "data->env_msh[size] after: %d\n", size); //
	// return (SUCCESS);
}
