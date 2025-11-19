/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_u_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:52:56 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 18:00:50 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	comma_num(char *line)
{
	int	i;
	int	count;

	if (!line)
		exit_error("Error: somthing went wrong!\n");
	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
		exit_error("Error: a lot of commas in a color!\n");
	else if (count < 2)
		exit_error("Error: too few commas in a color!\n");
}

void	valid_chars(t_data *data, char *value)
{
	int	i;
	int	index;

	if (!data || !value)
		exit_error("Error: Something went wrong!\n");
	i = -1;
	while (++i < 3)
	{
		index = 0;
		while (data->utils.rbgs[i][index])
		{
			if (!(data->utils.rbgs[i][index] == '+'
				|| data->utils.rbgs[i][index] == '-'
				|| (data->utils.rbgs[i][index] >= '0'
				&& data->utils.rbgs[i][index] <= '9')))
				exit_error("Error: invalid character in color!\n");
			index++;
		}
	}
}

void	rgb_only(char *line)
{
	int	i;

	if (!line)
		exit_error("Error: somrthing went wrong!\n");
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] == ' ')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] != '\0' && line[i] != ' ')
			exit_error("Error: invalid color line!\n");
	}
}

void	size_three(t_data *data)
{
	int	i;

	if (!data)
		exit_error("Error: something went wrong!\n");
	i = 0;
	while (i < 3)
	{
		if (is_in(data->utils.rbgs[i] + 1, "-+"))
			exit_error("Error: illegal operator in rgb!\n");
		if (num_len(data->utils.rbgs[i]) > 3 && is_in(data->utils.rbgs[i], "123456789"))
			exit_error("Error: rgb range: 0...255\n");
		i++;
	}	
}
