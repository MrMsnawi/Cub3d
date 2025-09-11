/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:41:55 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/11 19:18:26 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

# define NO	0
# define SO	1
# define WE	2
# define EA	3
# define F	4
# define C	5

bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	elmnts_init(int *arr)
{
	int i;

	i = 0;
	while (i < 6)
	{
		arr[i] = 0;
		i++;
	}
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

void	dup_check(int *arr)
{
	if (arr[NO] > 1)
		exit_error("Error: NO duplicated!\n");
	else if (arr[SO] > 1)
		exit_error("Error: SO duplicated!\n");
	else if (arr[WE] > 1)
		exit_error("Error: WE duplicated!\n");
	else if (arr[EA] > 1)
		exit_error("Error: EA duplicated!\n");
	else if (arr[F] > 1)
		exit_error("Error: F duplicated!\n");
	else if (arr[C] > 1)
		exit_error("Error: C duplicated!\n");
}

void	missing_check(int *arr)
{
	if (arr[NO] < 1)
		exit_error("Error: NO is missing!\n");
	else if (arr[SO] < 1)
		exit_error("Error: SO is missing!\n");
	else if (arr[WE] < 1)
		exit_error("Error: WE is missing!\n");
	else if (arr[EA] < 1)
		exit_error("Error: EA is missing!\n");
	else if (arr[F] < 1)
		exit_error("Error: F is missing!\n");
	else if (arr[C] < 1)
		exit_error("Error: C is missing!\n");
}

int	mo_wspaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return i;
}

void	missing_dup_check(t_data *data)
{
	int	i;
	int	offset;

	elmnts_init(data->elmnts);
	if (!data)
		exit_error("Error: Somthing went wrong!\n");
	i = 0;
	offset = 0;
	while (data->file_data[i])
	{
		offset = mo_wspaces(data->file_data[i]);
		if (!corr_size(data->file_data[i] + offset, 2) && (ft_strncmp(data->file_data[i] + offset, "NO", 2) == 0))
			data->elmnts[NO]++;
		else if (!corr_size(data->file_data[i] + offset, 2) && (ft_strncmp(data->file_data[i] + offset, "SO", 2) == 0))
			data->elmnts[SO]++;
		else if (!corr_size(data->file_data[i] + offset, 2) && (ft_strncmp(data->file_data[i] + offset, "WE", 2) == 0))
			data->elmnts[WE]++;
		else if (!corr_size(data->file_data[i] + offset, 2) && (ft_strncmp(data->file_data[i] + offset, "EA", 2) == 0))
			data->elmnts[EA]++;
		else if (!corr_size(data->file_data[i] + offset, 1) && (ft_strncmp(data->file_data[i] + offset, "F", 1) == 0))
			data->elmnts[F]++;
		else if (!corr_size(data->file_data[i] + offset, 1) && (ft_strncmp(data->file_data[i] + offset, "C", 1) == 0))
			data->elmnts[C]++;
		i++;
	}
	dup_check(data->elmnts);
	missing_check(data->elmnts);
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

bool	is_map_begin(char *line)
{
	if (!line)
		exit_error("Error: Somthing went wrong!\n");
	if (line[0] == '0' || line[0] == '1')
		return (true);
	return (false);
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

void	map_in_the_file(t_data *data)
{
	int	i;
	int	offset;

	if (!data)
		exit_error("Error: Somthing went wrong!\n");
	i = 0;
	offset = 0;
	while (data->file_data[i])
	{
		offset = mo_wspaces(data->file_data[i]);
		if (is_map_begin(data->file_data[i] + offset) && count_elements(data->file_data, i) != 6)
			exit_error("Error: the map must be the last element\n");
		i++;
	}
}

void	element_parse(t_data *data)
{
	if (!data)
		exit_error("Error: Somthing went wrong!\n");
	missing_dup_check(data);
	map_in_the_file(data);
	textures_parse(data);
	rgb_parse(data);
}

/*
NO
SO
WE
EA
F
C
*/
