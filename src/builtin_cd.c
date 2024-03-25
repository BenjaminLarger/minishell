/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:15:50 by blarger           #+#    #+#             */
/*   Updated: 2024/03/25 20:44:58 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FUNCTIONS
/* chdir will change the current directory of your program, probably a
command shell you are trying to implement. */

//IMPORTANT
/* - is a special argument for the cd command: cd - means to go back to the
previous current directory. To implement this functionality, you need to keep
track of the last directory cd changed to. Use the getcwd() function for that
before calling chdir and if successful, keep this previous directory in a global
array. 
~ is another special thing: it should be expanded to the home directory
(the valueof the HOME environment variable) before dispatching to the command
handler, so one can type cd ~, or just cd to change to the home directory but cd
"~" to change to a directory named "~". ~ should expand to $(HOME), either as a
stand alone string or as the initial portion of a path: ~/bin. Note that ~name
should expand to the home directory of the user name.*/

//HOW DOES IT WORK ?
/* Absolute and relative paths such as /, .., subdir pose no problem and
can be passed directly to the chdir system call.
use cases :
-> cd ~
-> cd ~/...
-> cd .
-> cd ..
-> cd -
-> cd ...
-> cd /.../
		 */

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
		ft_putstr_fd("minish: cd: ", 2);
		ft_putstr_fd(arg, 2);
		write(2, " ", 1);
		ft_putstr_fd(FILE, 2);
		return ;
	}
	if (chdir(arg))
	{
		ft_putstr_fd("minish: cd: ", 2);
		ft_putstr_fd(path, 2);
		write(2, " ", 1);
		ft_putstr_fd(FILE, 2);
	}
	ft_strlcpy(data->cd_last_dir, cur_dir, ft_strlen(data->cd_last_dir) + 1);
	free(path);
}

static void	cd_back_to_prev_cur_dir(char *arg, char *cur_dir, t_minishell *data)
{
	dprintf(2, "CD to %s\n", data->cd_last_dir);
	if (chdir(data->cd_last_dir) && arg)
		ft_putstr_fd("minish: cd: OLDPWD not set\n", 2);
	else
		printf("%s\n", data->cd_last_dir);
	ft_strlcpy(data->cd_last_dir, cur_dir, ft_strlen(cur_dir) + 1);
	free(cur_dir);
}

void	builtin_cd(char *arg, t_minishell *data) //Check the leaks. Else it should works perfectly
{
	char	*cur_dir;

	if (command_with_pipe(data->args) == TRUE)
		return ;
	cur_dir = NULL;
	cur_dir = getcwd(cur_dir, sizeof(cur_dir));
	if (arg == NULL)
		arg = ft_getenv(data, "HOME");
	if (!ft_strcmp(arg, "-"))
		return (cd_back_to_prev_cur_dir(arg, cur_dir, data));
	if (!ft_strncmp(arg, "~", 1))
		dispatch_home_dir(arg, cur_dir, data);
	else if (ft_strcmp(arg, "."))
	{
		if (chdir(arg))
		{
			ft_putstr_fd("minish: cd: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putchar_fd(' ', 2);
			ft_putstr_fd(FILE, 2);
		}
	}
	ft_strlcpy(data->cd_last_dir, cur_dir, ft_strlen(data->cd_last_dir) + 1);
	free(cur_dir);
}
