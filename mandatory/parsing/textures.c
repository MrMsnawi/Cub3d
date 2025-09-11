/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:20 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/11 18:33:27 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	txtr_prs_continue(t_data *data)
{
	if (!data)
		exit_error("Error: something went wrong!\n");
	data->no.img_path = get_element_value(data, "NO");
	if (data->no.img_path == NULL)
		exit_error("Error: can't find NO value!\n");
	data->no.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->no.img_path, \
		&data->no.widtht, &data->no.height);
	if (data->no.img_ptr == NULL)
		exit_error("Error: faild to initialize no image!\n");
	data->so.img_path = get_element_value(data, "SO");
	if (data->so.img_path == NULL)
		exit_error("Error: can't find SO value!\n");
	data->so.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->so.img_path, \
		&data->so.widtht, &data->so.height);
	if (data->so.img_ptr == NULL)
		exit_error("Error: faild to initialize SO image!\n");
}

void	textures_parse(t_data *data)
{
	if (!data)
		exit_error("Error: something went wrong!\n");
	data->ea.img_path = get_element_value(data, "EA");
	if (data->ea.img_path == NULL)
		exit_error("Error: can't find EA value!\n");
	data->ea.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->ea.img_path, \
		&data->ea.widtht, &data->ea.height);
	if (data->ea.img_ptr == NULL)
		exit_error("Error: faild to initialize EA image!\n");
	data->we.img_path = get_element_value(data, "WE");
	if (data->we.img_path == NULL)
		exit_error("Error: can't find WE value!\n");
	data->we.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->we.img_path, \
		&data->we.widtht, &data->we.height);
	if (data->we.img_ptr == NULL)
		exit_error("Error: faild to initialize WE image!\n");
	txtr_prs_continue(data);
}
