/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:20:43 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/12 10:12:50 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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

size_t	rgb_len(char *value, int offset)
{
	int	i;

	i = offset;
	while (value[i] && value[i] != ',' && !ft_isspace(value[i]))
		i++;
	return (i - offset);
}

void	fil_rbgs_arr(t_data *data, char *value)
{
	int	i;
	int	offset;
	int	index;

	if (!data || !value)
		exit_error("Error: Something went wrong!\n");
	data->utils.rbgs = malloc(sizeof(char *) * 3);
	if (!data->utils.rbgs)
		exit_error("Error: oh!\n");
	i = 0;
	offset = 0;
	while (i < 3)
	{
		index = 0;
		data->utils.rbgs[i] = malloc(rgb_len(value, offset) + 1);
		if (!data->utils.rbgs)
			exit_error("Error: oh!\n");
		while (value[offset] && value[offset] != ',' && !ft_isspace(value[offset]))
			data->utils.rbgs[i][index++] = value[offset++];
		data->utils.rbgs[i][index] = '\0';
		i++;
		offset++;
	}
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
			if (!(data->utils.rbgs[i][index] == '+' || data->utils.rbgs[i][index] == '-'
				|| (data->utils.rbgs[i][index] >= '0' && data->utils.rbgs[i][index] <= '9')))
				exit_error("Error: invalid character in color!\n");
			index++;
		}
	}
}

bool	is_in(char *str, char *set)
{
	int		i;
	int		j;
	int		count_check;

	if (!str || !set)
		exit_error("Error: Something went wrong!\n");
	i = 0;
	count_check = 0;
	while (set[i])
	{
		j = 0;
		while (str[j])
		{
			if (str[j] == set[i])
			{
				count_check++;
				break ;
			}
			j++;
		}
		i++;
	}
	if (count_check)
		return (true);
	return (false);
}

int	num_len(char *str)
{
	int	i;
	int	count;
	
	if (!str)
		exit_error("Error: something went wrong!\n");
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			count++;
		i++;
	}
	return (count);
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
		if (num_len(data->utils.rbgs[i]) > 3)
			exit_error("Error: rgb range: 0...255\n");
		i++;
	}	
}

int	a_to_rgb_i(char *str)
{
	int	i;
	int	res;

	if (!str)
		exit_error("Error: something went wrong!\n");
	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			exit_error("Error: rgb range: 0...255\n");
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0' && !(str[i] >= '0' && str[i] <= '9'))
		exit_error("Error: 654invalid rgb character!\n");
	if (res > 255)
		exit_error("Error: rgb range: 0...255\n");
	return (res);
}

int	int32bit_rgb(int *i_rbg, char **rbgs)
{
	if (!rbgs || !*rbgs)
		exit_error("Error: something went wrong!\n");
	i_rbg[T] = 0;
	i_rbg[R] = a_to_rgb_i(rbgs[0]);
	i_rbg[G] = a_to_rgb_i(rbgs[1]);
	i_rbg[B] = a_to_rgb_i(rbgs[2]);
	return (i_rbg[T] << 24 | i_rbg[R] << 16 | i_rbg[G] << 8 | i_rbg[B]);
}

int	parsed_rgb(t_data *data, char *value)
{
	if (!data || !value)
		exit_error("Error: Something went wrong!\n");
	rgb_only(value);
	comma_num(value);
	fil_rbgs_arr(data, value);
	valid_chars(data, value);
	size_three(data);
	return (int32bit_rgb(data->utils.i_rbg, data->utils.rbgs));
	return 0;
}

int	get_rgb_int(t_data *info, char **data, char *elmnt)
{
	int	rgb;
	int	line_index;
	int	line_col;

	if (!data || !*data || !info)
		exit_error("Error: Somthing went wrong!\n");
	rgb = 0;
	line_col = 1;
	if (ft_strncmp(elmnt, "F", 1) == 0 || ft_strncmp(elmnt, "C", 1) == 0)
	{
		line_index = get_line_index(data, elmnt);
		if (line_index == -1)
			exit_error("Error: can't find rgb index!\n");
		line_col += mo_wspaces(data[line_index]) + 1;
		line_col += mo_wspaces(data[line_index] + line_col);
		rgb = parsed_rgb(info, data[line_index] + line_col);
	}
	else
		exit_error("Error: Wrong element type!\n");
	return (rgb);
}

void	rgb_parse(t_data *data)
{
	if (!data)
		exit_error("Error: Something went wrong!\n");
	data->f = get_rgb_int(data, data->file_data, "F");
	data->c = get_rgb_int(data, data->file_data, "C");
}
