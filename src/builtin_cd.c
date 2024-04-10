/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:15:50 by blarger           #+#    #+#             */
/*   Updated: 2024/04/10 16:44:28 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(t_minishell *data)
{
	if (ft_getenv(data, "HOME"))
	{
		return (ft_getenv(data, "HOME"));
	}
	else if (ft_getenv(data, ""))
		return (ft_getenv(data, "ZDOTDIR"));
	else if (ft_getenv(data, "USER_ZDOTDIR"))
		return (ft_getenv(data, "USER_ZDOTDIR"));
	else
		return (NULL);
}

static void	dispatch_home_dir(char *arg, char *cur_dir, t_minishell *data)
{
	char	*path;

	path = NULL;
	if ((arg[1] == '/' || arg[1] == '\0') && get_home_path(data))
	{
		path = gnl_strjoin(get_home_path(data), arg + 1);
		arg = path;
	}
	else
	{
		print_error_cd(arg, data, FILE);
		return ;
	}
	if (chdir(arg))
	{
		print_error_cd(arg, data, FILE);
	}
	ft_strlcpy(data->cd_last_dir, cur_dir, ft_strlen(data->cd_last_dir) + 1);
	free(path);
}

static void	cd_back_to_prev_cur_dir(char *arg, char *cur_dir, t_minishell *data)
{
	if (data->is_start == TRUE && arg)
	{
		ft_putstr_fd("minish: cd: OLDPWD not set\n", 2);
		data->last_exit_status = 1;
	}
	else
		printf("%s\n", data->cd_last_dir);
	ft_strlcpy(data->cd_last_dir, cur_dir, ft_strlen(cur_dir) + 1);
	free(cur_dir);
}

void	export_pwd_or_old_pwd(t_minishell *data, char *dir, char *pwd)
{
	char	**args;
	char	*value;
	int		i;

	i = 0;
	args = (char **)malloc(sizeof(char *) * 3);
	if (!args)
		return (ft_putstr_fd(MALLOC_FAIL, 2));
	value = ft_strdup(dir);
	if (!value)
		return (print_strerror_and_set_exit_status(data));
	args[0] = ft_strdup("export");
	if (!args[0])
		return (print_strerror_and_set_exit_status(data));
	args[1] = ft_strjoin(pwd, dir);
	if (!args[1])
		return (print_strerror_and_set_exit_status(data));
	args[2] = NULL;
	builtin_export(args, data);
	free(value);
	free_string_array(args);
}

void	builtin_cd(char *arg, t_minishell *data)
{
	char	*cur_dir;

	data->last_exit_status = 0;
	if (command_with_pipe(data->args) == TRUE)
		return ;
	cur_dir = NULL;
	cur_dir = getcwd(cur_dir, sizeof(cur_dir));
	if (arg == NULL)
		arg = ft_getenv(data, "HOME");
	if (!cur_dir)
		chdir(ft_getenv(data, "HOME"));
	else if (!ft_strcmp(arg, "-"))
		return (cd_back_to_prev_cur_dir(arg, cur_dir, data));
	else if (!ft_strncmp(arg, "~", 1))
		dispatch_home_dir(arg, cur_dir, data);
	else if (ft_strcmp(arg, ".") && chdir(arg))
		print_error_cd(arg, data, FILE);
	if (cur_dir)
	{
		ft_strlcpy(data->cd_last_dir, cur_dir, ft_strlen(cur_dir) + 1);
		if (data->is_start == FALSE && data->cd_last_dir)
			export_pwd_or_old_pwd(data, data->cd_last_dir, "OLDPWD=");
	}
	free(cur_dir);
}
