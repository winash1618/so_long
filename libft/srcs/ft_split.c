/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 09:01:12 by mkaruvan          #+#    #+#             */
/*   Updated: 2023/05/23 07:16:38 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count(char const *s, char c)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			l++;
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			l++;
		i++;
	}
	return (l);
}

static char	**splitter(char const *s, char c, char **str, int *i)
{
	while (i[0] < i[4])
	{
		i[1] = 0;
		while (s[i[2]] == c && s[i[2]])
			i[2]++;
		while (s[i[2]] != c && s[i[2]])
		{
			i[1]++;
			i[2]++;
		}
		str[i[0]] = (char *)malloc(sizeof(char) * (i[1] + 1));
		i[2] -= i[1];
		i[3] = 0;
		while (s[i[2]] != c && s[i[2]])
		{
			str[i[0]][i[3]] = s[i[2]];
			i[3]++;
			i[2]++;
		}
		str[i[0]++][i[3]] = '\0';
	}
	str[i[0]] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i[5];
	int		j;

	j = 0;
	while (j < 5)
		i[j++] = 0;
	if (!s)
		return (NULL);
	i[4] = count(s, c);
	str = (char **) malloc(sizeof(*str) * (i[4] + 1));
	if (!str)
		return (NULL);
	return (splitter(s, c, str, i));
}
