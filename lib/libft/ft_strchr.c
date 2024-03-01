/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demre <demre@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:05:35 by demre             #+#    #+#             */
/*   Updated: 2023/12/02 19:40:08 by demre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && (unsigned char)*s != (unsigned char)c)
		s++;
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
int main()
{
	printf("%s\n", strchr("aa4cc4dd", '4'));
	printf("%s\n", ft_strchr("aa4cc4dd", '4'));
	printf("%s\n", strchr("aa4cc4dd", '4' + 256));
	printf("%s\n", ft_strchr("aa4cc4dd", '4' + 256));
	return 0;
}
*/