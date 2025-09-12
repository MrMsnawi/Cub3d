/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:22:18 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/12 22:07:31 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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

// void	fill_map(t_data *data, int index)
// {
// 	int	i;
// 	int	len;

// 	if (!data)
// 		exit_error("Error: Something went wrong!\n");
// 	len = map_len(data->file_data, index);
// 	data->utils.map = malloc(sizeof(char *) * (len + 1));
// 	if (!data->utils.map)
// 		exit_error("Error: oh hhhh\n");
// 	data->utils.map[len] = NULL;
// 	i = 0;
// 	while (data->file_data[index])
// 	{
// 		data->utils.map[i] = ft_strdup(data->file_data[index]);
// 		if (!data->utils.map[i])
// 			exit_error("Error: strdup!\n");
// 		i++;
// 		index++;
// 	}
// }

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
			data->utils.map[i][j++] = ' ';
		data->utils.map[i][j] = '\0';
		return (0);
	}
	k = 0;
	data->utils.map[i][j++] = ' ';
	while (data->file_data[index][k])
		data->utils.map[i][j++] = data->file_data[index][k++];
	while (j < data->utils.map_width)
		data->utils.map[i][j++] = ' ';
	data->utils.map[i][j] = '\0';
	return (1);
}

void	fill_map(t_data *data, int index)
{
	int	i;

	if (!data)
		exit_error("Error: Something went wrong!\n");
	data->utils.map_height = map_len(data->file_data, index) + 2;
	data->utils.map = malloc(sizeof(char *) * (data->utils.map_height + 1));
	if (!data->utils.map)
		exit_error("Error: oh hhhh\n");
	data->utils.map[data->utils.map_height] = NULL;
	data->utils.map_width = get_max_row(data->file_data, index);
	i = 0;
	while (i < data->utils.map_height)
	{
		data->utils.map[i] = malloc(data->utils.map_width + 1);
		if (!data->utils.map[i])
			exit_error("Error: oh no\n");
		index += fill_row(data, i, index);
		i++;
	}
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

void	characters(t_data *data)
{
	int	i;
	int	j;
	int	spcl_char;

	if (!data)
		exit_error("Error: Something went wrong!\n");
	i = 0;
	spcl_char = 0;
	while (data->utils.map[i])
	{
		j = 0;
		while (data->utils.map[i][j])
		{
			if (!much(data->utils.map[i][j], " 01NSEW"))
				exit_error("Error: invalid character in the map! \" 01NSEW\"\n");
			if (much(data->utils.map[i][j], "NSEW"))
				spcl_char++;
			if (spcl_char > 1)
				exit_error("Error: Must be one player!\n");
			j++;
		}
		i++;
	}
}

// one flood fill begin from [0,0]
void	elmnt_triage(t_data *data, int x, int y)
{
	if (!data)
		exit_error("Error: Something went wrong!\n");
	if (x < 0 || x >= data->utils.map_height)
		return ;
	if (y < 0 || y >= data->utils.map_width)
		return ;
	if (data->utils.map[x][y] == 'v')
		return ;
	if (data->utils.map[x][y] == 'N' || data->utils.map[x][y] == 'S'
		|| data->utils.map[x][y] == 'E' || data->utils.map[x][y] == 'W')
		exit_error("Error: the player must be inside the map!\n");
	if (data->utils.map[x][y] != '1' && data->utils.map[x][y] != ' ')
	{
		printf(" %c\n", data->utils.map[x-1][y]);
		printf("%c%c%c\n", data->utils.map[x][y-1], data->utils.map[x][y], data->utils.map[x][y+1]);
		printf(" %c\n", data->utils.map[x+1][y]);
		exit_error("Error: the map must be surrounded by walls!\n");
	}
	data->utils.map[x][y] = 'v';
	elmnt_triage(data, x + 1, y);
	elmnt_triage(data, x - 1, y);
	elmnt_triage(data, x, y + 1);
	elmnt_triage(data, x, y - 1);
}

void	map_process(t_data *data)
{
	int	index;
	char	**visited;
	// copy the map into visited 2d array and use it as reference for visited positions

	if (!data)
		exit_error("Error: Something went wrong!\n");
	index = map_1st_line_index(data->file_data);
	fill_map(data, index);
	characters(data);
	// printf("%d %d\n", data->utils.map_width, data->utils.map_height);
	// for (int i = 0; data->utils.map[0][i]; i++)
	// 	printf("%c %d\n", data->utils.map[0][i], i);
	elmnt_triage(data, 0, 0);
}

/*
	test with N111111111111 in first line of map
*/
