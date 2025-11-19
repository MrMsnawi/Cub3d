/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elmnts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:40:17 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 18:11:03 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	elmnts_init(int *arr)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		arr[i] = 0;
		i++;
	}
}

int	mo_wspaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

bool	is_valid_element(char *line)
{
	if (!line)
		exit_error("Error: Somthing went wrong!\n");
	return (ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0
		|| ft_strncmp(line, "C", 1) == 0);
}

int	corr_size(char *line, int size)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (i != size)
		return (1);
	return (0);
}

int	count_elements(char **line, int end)
{
	int	i;
	int	offset;
	int	count;

	if (!line)
		exit_error("Error: Somthing went wrong!\n");
	i = 0;
	count = 0;
	offset = 0;
	while (i <= end)
	{
		offset = mo_wspaces(line[i]);
		if (ft_strncmp(line[i] + offset, "NO", 2) == 0
			|| ft_strncmp(line[i] + offset, "SO", 2) == 0
			|| ft_strncmp(line[i] + offset, "WE", 2) == 0
			|| ft_strncmp(line[i] + offset, "EA", 2) == 0
			|| ft_strncmp(line[i] + offset, "F", 1) == 0
			|| ft_strncmp(line[i] + offset, "C", 1) == 0)
			count++;
		i++;
	}
	return (count);
}
