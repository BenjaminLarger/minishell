/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_replace_env_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:11 by demre             #+#    #+#             */
/*   Updated: 2024/03/19 14:59:15 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_until_env_var(char const *input, int *i, int *expanded_length)
{
	while (input[*i] && input[*i] != '$')
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
		move_until_env_var(input, &i, &expanded_length);
		if (input[i] == '$')
		{
			ev_start = ++i;
			while (i < input_len && input[i] != '$' && input[i] != ' ')
				i++;
			temp_ev_name = ft_substr(input, ev_start, i - ev_start);
			if (!temp_ev_name)
				return (-1);
			expanded_length += ft_strlen(getenv(temp_ev_name));
			free(temp_ev_name);
		}
		else
			i++;
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

char	*ft_substr_with_env_var(char const *input, int input_idx, int input_len)
{
	char	*expanded;
	int		expanded_length;
	int		exp_idx;
	char	*temp_ev_value;
	char	*temp_ev_name;
	int		ev_start;

	if (ft_memchr(&input[input_idx], '$', input_len) == NULL)
		return (ft_substr(input, input_idx, input_len));
	if (get_expanded_length(input, input_len, &expanded_length) == -1)
			return (NULL);
	expanded = (char *)malloc((expanded_length + 1) * sizeof(char));
	if (!expanded)
		return (NULL);
	exp_idx = 0;
	ev_start = 0;
	while (exp_idx < expanded_length - 1 && input[input_idx] != '\0')
	{
		if (input[input_idx] == '$')
		{
			ev_start = ++input_idx;
			while (input_idx < input_len && input[input_idx] != '$' && input[input_idx] != ' ')
				input_idx++;
			temp_ev_name = ft_substr(input, ev_start, input_idx - ev_start);
			if (!temp_ev_name)
				return (NULL);
			temp_ev_value = getenv(temp_ev_name);
			if (temp_ev_value != NULL)
			{
				while (*temp_ev_value)
					expanded[exp_idx++] = *temp_ev_value++;
				free(temp_ev_name);				
				while (input_idx < input_len && input[input_idx] != '$' && input[input_idx] != ' ')
					input_idx++;
			}
		}
		else
			expanded[exp_idx++] = input[input_idx++];
	}
	expanded[exp_idx] = '\0';
	dprintf(2, "expanded: %s\n", expanded);
	return (expanded);
}
