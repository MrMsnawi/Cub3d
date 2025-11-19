/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:45:58 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 15:34:54 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static size_t	words(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			++cnt;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (cnt);
}

static int	allocation(char ***buf, size_t words)
{
	*buf = (char **)ft_malloc((words + 1) * sizeof(char *));
	if (*buf == NULL)
		return (0);
	return (1);
}

char	**ft_split(char *s, char c)
{
	int		i;
	char	*from;
	char	**buf;

	if (s == NULL)
		return (NULL);
	if (allocation(&buf, words(s, c)) == 0)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			from = (char *)s;
			while (*s && *s != c)
				++s;
			buf[i++] = ft_substr(from, 0, ((char *)s - from));
			if (buf[i - 1] == NULL)
				exit_error("Error: substring!\n");
		}
		else
			++s;
	}
	buf[i] = NULL;
	return (buf);
}
