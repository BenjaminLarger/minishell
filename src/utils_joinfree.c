/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_joinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:30:08 by blarger           #+#    #+#             */
/*   Updated: 2024/03/05 09:30:43 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *str);

char	*jointure_free(char *str, const char *s2, int i, int length)
{
	int	j;

	j = 0;
	while (j < length)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		l1;
	int		l2;
	char	*str;

	l1 = 0;
	l2 = 0;
	if (s1 != NULL)
		l1 = ft_strlen(s1);
	if (s2 != NULL)
		l2 = ft_strlen(s2);
	str = (char *)malloc((l1 + l2 + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (i < l1)
	{
		str[i] = s1[i];
		i++;
	}
	jointure_free(str, s2, i, l2);
	str[l1 + l2] = '\0';
	free(s1);
	return (str);
}
