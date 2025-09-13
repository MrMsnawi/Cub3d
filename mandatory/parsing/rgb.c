/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:20:43 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 18:01:19 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	fil_rbgs_arr(t_data *data, char *val)
{
	int	i;
	int	offset;
	int	index;

	if (!data || !val)
		exit_error("Error: Something went wrong!\n");
	data->utils.rbgs = ft_malloc(sizeof(char *) * 3);
	if (!data->utils.rbgs)
		exit_error("Error: oh!\n");
	i = 0;
	offset = 0;
	while (i < 3)
	{
		index = 0;
		data->utils.rbgs[i] = ft_malloc(rgb_len(val, offset) + 1);
		if (!data->utils.rbgs)
			exit_error("Error: oh!\n");
		while (val[offset] && val[offset] != ',' && !ft_isspace(val[offset]))
			data->utils.rbgs[i][index++] = val[offset++];
		data->utils.rbgs[i][index] = '\0';
		i++;
		offset++;
	}
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
	data->f = get_rgb_int(data, data->utils.file_data, "F");
	data->c = get_rgb_int(data, data->utils.file_data, "C");
}
