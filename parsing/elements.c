/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:41:55 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 17:45:43 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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

void	md_helper(t_data *data, int offset, int i)
{
	if (!corr_size(data->utils.file_data[i] + offset, 2)
		&& (ft_strncmp(data->utils.file_data[i] + offset, "NO", 2) == 0))
		data->utils.elmnts[NO]++;
	else if (!corr_size(data->utils.file_data[i] + offset, 2)
		&& (ft_strncmp(data->utils.file_data[i] + offset, "SO", 2) == 0))
		data->utils.elmnts[SO]++;
	else if (!corr_size(data->utils.file_data[i] + offset, 2)
		&& (ft_strncmp(data->utils.file_data[i] + offset, "WE", 2) == 0))
		data->utils.elmnts[WE]++;
	else if (!corr_size(data->utils.file_data[i] + offset, 2)
		&& (ft_strncmp(data->utils.file_data[i] + offset, "EA", 2) == 0))
		data->utils.elmnts[EA]++;
	else if (!corr_size(data->utils.file_data[i] + offset, 1)
		&& (ft_strncmp(data->utils.file_data[i] + offset, "F", 1) == 0))
		data->utils.elmnts[F]++;
	else if (!corr_size(data->utils.file_data[i] + offset, 1)
		&& (ft_strncmp(data->utils.file_data[i] + offset, "C", 1) == 0))
		data->utils.elmnts[C]++;
	else if (data->utils.file_data[i][offset] != '1'
		&& data->utils.file_data[i][offset] != '0')
		exit_error("Error: Invalid element!\n");
}

void	missing_dup_check(t_data *data)
{
	int	i;
	int	offset;

	elmnts_init(data->utils.elmnts);
	if (!data)
		exit_error("Error: Something went wrong!\n");
	i = 0;
	offset = 0;
	while (data->utils.file_data[i])
	{
		offset = mo_wspaces(data->utils.file_data[i]);
		md_helper(data, offset, i);
		i++;
	}
	dup_check(data->utils.elmnts);
	missing_check(data->utils.elmnts);
}

void	element_parse(t_data *data)
{
	if (!data)
		exit_error("Error: Something went wrong!\n");
	missing_dup_check(data);
	map_in_the_file(data);
	textures_parse(data);
	rgb_parse(data);
	map_process(data);
}
