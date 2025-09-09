/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:41:55 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/09 19:26:46 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

# define NO	0
# define SO	1
# define WE	2
# define EA	3
# define F	4
# define C	5

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
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	if (i != size)
		return (1);
	return (0);
}

void	dup_monitor(int *arr)
{
	if (arr[NO] != 2)
		exit_error("Error: NO duplicated!\n");
	else if (arr[SO] != 2)
		exit_error("Error: SO duplicated!\n");
	else if (arr[WE] != 2)
		exit_error("Error: WE duplicated!\n");
	else if (arr[EA] != 2)
		exit_error("Error: EA duplicated!\n");
	else if (arr[F] != 1)
		exit_error("Error: F duplicated!\n");
	else if (arr[C] != 1)
		exit_error("Error: C duplicated!\n");
}

void	check_element_duplications(t_data *data)
{
	int	i;
	int	elmnts[6];

	elmnts_init(elmnts);
	if (!data)
		exit_error("Error: Somthing went wrong!\n");
	i = 0;
	while (data->file_data[i])
	{
		// check size of element until reach space
		if (!corr_size(data->file_data[i], 2) && (ft_strncmp(data->file_data[i], "NO", 2) == 0))
			elmnts[NO]++;
		else if (!corr_size(data->file_data[i], 2) && (ft_strncmp(data->file_data[i], "SO", 2) == 0))
			elmnts[SO]++;
		else if (!corr_size(data->file_data[i], 2) && (ft_strncmp(data->file_data[i], "WE", 2) == 0))
			elmnts[WE]++;
		else if (!corr_size(data->file_data[i], 2) && (ft_strncmp(data->file_data[i], "EA", 2) == 0))
			elmnts[EA]++;
		else if (!corr_size(data->file_data[i], 1) && (ft_strncmp(data->file_data[i], "F", 1) == 0))
			elmnts[F]++;
		else if (!corr_size(data->file_data[i], 1) && (ft_strncmp(data->file_data[i], "C", 1) == 0))
			elmnts[C]++;
		i++;
	}
	dup_monitor(elmnts);
}

void	element_parse(t_data *data)
{
	if (!data)
		exit_error("Error: Somthing went wrong!\n");
	check_element_duplications(data);
}

/*
NO
SO
WE
EA
F
C
*/
