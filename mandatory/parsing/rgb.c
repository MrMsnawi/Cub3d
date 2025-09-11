/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:20:43 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/11 19:48:21 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	get_rgb_int(char **data)
{
	if (!data || !*data)
		exit_error("Error: Somthing went wrong!\n");
	
}

void	rgb_parse(t_data *data)
{
	if (!data)
		exit_error("Error: Something went wrong!\n");
	data->f = get_rgb_int(data->file_data);
	data->c = get_rgb_int(data->file_data);
}

/*
2 commas ','
store between commas int 2d array
while over the numbers and check if it contain invalid char
valid ==> + (0-->9)
size more than 3 chars proceed to message tell that the number > 255
convert values to int
shift values into one int
store the value in the data struct
*/
