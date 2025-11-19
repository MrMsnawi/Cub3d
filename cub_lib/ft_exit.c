/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:45:00 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 17:37:14 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_data	**get_data_ptr(void)
{
	static t_data	*data;

	return (&data);
}

void	set_data_ptr(t_data *data)
{
	t_data	**data_ptr;

	data_ptr = get_data_ptr();
	*data_ptr = data;
}

void	mlx_free(t_data *data)
{
	if (!data)
		return ;
	if (!data->mlx_ptr)
		return ;
	if (data->image.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->image.img_ptr);
	if (data->no.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->no.img_ptr);
	if (data->so.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->so.img_ptr);
	if (data->we.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->we.img_ptr);
	if (data->ea.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->ea.img_ptr);
	if (data->window)
		mlx_destroy_window(data->mlx_ptr, data->window);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

void	ft_exit(int exit_status)
{
	t_data	**data_ptr;

	data_ptr = get_data_ptr();
	if (data_ptr && *data_ptr)
		mlx_free(*data_ptr);
	ft_free();
	exit(exit_status);
}
