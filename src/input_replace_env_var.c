/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_replace_env_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:11 by demre             #+#    #+#             */
/*   Updated: 2024/03/19 20:24:43 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_until_env_var(char const *input, int input_len, int *i,
	int *expanded_length)
{
	while (*i < input_len && input[*i] && input[*i] != '$')
	{
		(*i)++;
		(*expanded_length)++;
	}
}

static int	calculate_expanded_length(char const *input, int input_len)
{
	int		expanded_length;
	int		ev_start;
	int		i;
	char	*temp_ev_name;

	expanded_length = 0;
	i = 0;
	while (i < input_len && input[i])
	{
	dprintf(2, "input: %s, input_len: %d, i: %d, input[i]: %c, expanded_length: %d\n", input, input_len, i, input[i], expanded_length);
		move_until_env_var(input, input_len, &i, &expanded_length);
	dprintf(2, "input: %s, input_len: %d, i: %d, input[i]: %c, expanded_length: %d\n", input, input_len, i, input[i], expanded_length);
		if (input[i] == '$' && (i + 1) < input_len && input[i + 1] && is_valid_ev_character(input[i + 1])) // && input[i + 1] != ' '
		{
			dprintf(2, "1\n");
			ev_start = ++i;
			while (i < input_len && is_valid_ev_character(input[i])) // && input[i] != '$' && input[i] != ' '
				i++;
			temp_ev_name = ft_substr(input, ev_start, i - ev_start);
			if (!temp_ev_name)
				return (-1);
			if (getenv(temp_ev_name))
				expanded_length += ft_strlen(getenv(temp_ev_name));
			dprintf(2, "temp_ev_name: %s, getenv(temp_ev_name): %s, expanded_length: %d, i: %d\n", temp_ev_name, getenv(temp_ev_name), expanded_length, i);
			free(temp_ev_name);
		}
		else if (input[i++] == '$')
		{
			dprintf(2, "2\n");
			expanded_length++;
		}
		else
		{
			dprintf(2, "3\n");
			i++;
		}
	}
	dprintf(2, "returning exp_len: %d, i: %d\n\n", expanded_length, i);
	return (expanded_length);
}

static int	get_expanded_length(char const *input, int input_len,
	int *expanded_length)
{
	if (!input || input[0] == '\0')
		*expanded_length = 0;
	else
		*expanded_length = calculate_expanded_length(input, input_len);
	return (*expanded_length);
}

char	*ft_substr_with_env_var(char const *input, int input_len)
{
	char	*expanded;
	int		expanded_length;
	int		exp_idx;
	char	*temp_ev_value;
	char	*temp_ev_name;
	int		ev_start;
	int		i;

	i = 0;
	if (ft_memchr(input, '$', input_len) == NULL)
		return (ft_substr(input, i, input_len));
	if (get_expanded_length(input, input_len, &expanded_length) == -1)
		return (NULL);
	expanded = (char *)malloc((expanded_length + 1) * sizeof(char));
	if (!expanded)
		return (NULL);
	exp_idx = 0;
	ev_start = 0;
	while (exp_idx < expanded_length && input[i] != '\0')
	{
		if (input[i] == '$' && (i + 1) < input_len
			&& input[i + 1] && is_valid_ev_character(input[i + 1])) // && input[i + 1] != ' ' 
		{
			ev_start = ++i;
			while (i < input_len && is_valid_ev_character(input[i])) // && input[i] != '$' && input[i] != ' '
				i++;
			temp_ev_name = ft_substr(input, ev_start, i - ev_start);
			if (!temp_ev_name)
				return (NULL);
			temp_ev_value = getenv(temp_ev_name);
			if (temp_ev_value != NULL)
			{
				dprintf(2, "temp_ev_name: %s, getenv(temp_ev_name): %s, i: %d\n", temp_ev_name, getenv(temp_ev_name), i);
				while (*temp_ev_value)
					expanded[exp_idx++] = *temp_ev_value++;
				free(temp_ev_name);
			}
		}
		else
		{
			dprintf(2, "input[%d]: %c, exp_idx: %d/%d\n", i, input[i], exp_idx, expanded_length);
			expanded[exp_idx++] = input[i++];
		}
	}
	expanded[exp_idx] = '\0';
	dprintf(2, "expanded: %s\n", expanded);
	return (expanded);
}
