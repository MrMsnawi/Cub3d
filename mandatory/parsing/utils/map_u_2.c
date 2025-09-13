/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_u_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:05:00 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 18:05:57 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	map_in_the_file(t_data *data)
{
	int	i;
	int	offset;

	if (!data)
		exit_error("Error: Somthing went wrong!\n");
	i = 0;
	offset = 0;
	while (data->utils.file_data[i])
	{
		offset = mo_wspaces(data->utils.file_data[i]);
		if (is_map_begin(data->utils.file_data[i] + offset)
			&& count_elements(data->utils.file_data, i) != 6)
			exit_error("Error: the map must be the last element\n");
		i++;
	}
}

void	copy_map(t_data *data)
{
	int	i;

	if (!data)
		exit_error("Error: Something went wrong!\n");
	data->utils.copy = ft_malloc(sizeof(char *) * (data->utils.map_height + 1));
	if (!data->utils.copy)
		exit_error("Error: ft_malloc hhh\n");
	i = 0;
	while (data->map[i])
	{
		data->utils.copy[i] = ft_strdup(data->map[i]);
		if (!data->utils.copy[i])
			exit_error("Error: strdup hhh\n");
		i++;
	}
	data->utils.copy[i] = NULL;
}
