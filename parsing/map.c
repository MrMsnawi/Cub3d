/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:22:18 by abmasnao          #+#    #+#             */
/*   Updated: 2025/12/09 13:33:36 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	fill_row(t_data *data, int i, int index)
{
	int	j;
	int	k;

	if (!data)
		exit_error("Error: Something went wrong!\n");
	j = 0;
	if (i == 0 || i == data->utils.map_height - 1)
	{
		while (j < data->utils.map_width)
			data->map[i][j++] = ' ';
		data->map[i][j] = '\0';
		return (0);
	}
	k = 0;
	data->map[i][j++] = ' ';
	while (data->utils.file_data[index][k])
		data->map[i][j++] = data->utils.file_data[index][k++];
	while (j < data->utils.map_width)
		data->map[i][j++] = ' ';
	data->map[i][j] = '\0';
	return (1);
}

void	fill_map(t_data *data, int index)
{
	int	i;

	if (!data)
		exit_error("Error: Something went wrong!\n");
	data->utils.map_height = map_len(data->utils.file_data, index) + 2;
	data->map = ft_malloc(sizeof(char *) * (data->utils.map_height + 1));
	if (!data->map)
		exit_error("Error: oh hhhh\n");
	data->map[data->utils.map_height] = NULL;
	data->utils.map_width = get_max_row(data->utils.file_data, index);
	i = 0;
	while (i < data->utils.map_height)
	{
		data->map[i] = ft_malloc(data->utils.map_width + 1);
		if (!data->map[i])
			exit_error("Error: oh no\n");
		index += fill_row(data, i, index);
		i++;
	}
}

void	characters(t_data *data)
{
	int	i;
	int	j;
	int	spcl_char;

	if (!data)
		exit_error("Error: Something went wrong!\n");
	i = 0;
	spcl_char = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!much(data->map[i][j], " 01NSEW"))
				exit_error(INVALID_CHARACTER);
			if (much(data->map[i][j], "NSEW"))
			{
				spcl_char++;
				characters_helper(data, spcl_char, i, j);
			}
			j++;
		}
		i++;
	}
}

void	elmnt_triage(t_data *data, int x, int y)
{
	if (!data)
		exit_error("Error: Something went wrong!\n");
	if (x < 0 || x >= data->utils.map_height)
		exit_error("Error: the map must be surrounded by walls!\n");
	if (y < 0 || y >= data->utils.map_width)
		exit_error("Error: the map must be surrounded by walls!\n");
	if (data->utils.copy[x][y] == 'A' || data->utils.copy[x][y] == '1')
		return ;
	if (data->utils.copy[x][y] == 'N' || data->utils.copy[x][y] == 'S'
		|| data->utils.copy[x][y] == 'E' || data->utils.copy[x][y] == 'W'
		|| data->utils.copy[x][y] == '0' || data->utils.copy[x][y] == ' ')
		data->utils.copy[x][y] = 'A';
	else
		exit_error("Error: the map must be surrounded by walls!\n");
	elmnt_triage(data, x + 1, y);
	elmnt_triage(data, x - 1, y);
	elmnt_triage(data, x, y + 1);
	elmnt_triage(data, x, y - 1);
}

void	map_process(t_data *data)
{
	int	index;
	int i;
	int j;

	if (!data)
		exit_error("Error: Something went wrong!\n");
	index = map_1st_line_index(data->utils.file_data);
	fill_map(data, index);
	copy_map(data);
	characters(data);
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				data->map[i][j] = '0';
			j++;
		}
		i++;
	}
	elmnt_triage(data, data->utils.pos[0], data->utils.pos[1]);
}
