/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_u_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:43:47 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 18:10:59 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

bool	is_map_begin(char *line)
{
	if (!line)
		exit_error("Error: Somthing went wrong!\n");
	if (line[0] == '0' || line[0] == '1')
		return (true);
	return (false);
}

size_t	map_len(char **data, int index)
{
	int	count;

	if (!data || !*data)
		exit_error("Error: Something went wrong!\n");
	count = 0;
	while (data[index])
	{
		count++;
		index++;
	}
	return (count);
}

int	get_max_row(char **map, int index)
{
	int	len;

	if (!map || !*map)
		exit_error("Error: Something went wrong!\n");
	len = 0;
	while (map[index])
	{
		if (len < (int)ft_strlen(map[index]))
			len = (int)ft_strlen(map[index]);
		index++;
	}
	return (len + 2);
}

int	map_1st_line_index(char **data)
{
	int	i;
	int	offset;

	if (!data || !*data)
		exit_error("Error: Something went wrong!\n");
	i = 0;
	offset = 0;
	while (data[i])
	{
		offset = mo_wspaces(data[i]);
		if (data[i][offset] == '1' || data[i][offset] == '0')
			return (i);
		i++;
	}
	return (exit_error("Error: can't find map!\n"), -1);
}

bool	much(char c, char *set)
{
	int	i;

	if (!set)
		exit_error("Error: Something went wrong!\n");
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}
