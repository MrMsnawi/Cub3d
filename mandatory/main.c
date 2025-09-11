/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:38:13 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/11 18:40:14 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

void	ft_exit(int	exit_status)
{
	// ft_free();
	exit(exit_status);
}

int	win_close(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->image.img_ptr);
	mlx_destroy_image(data->mlx_ptr, data->no.img_ptr);
	mlx_destroy_image(data->mlx_ptr, data->so.img_ptr);
	mlx_destroy_image(data->mlx_ptr, data->we.img_ptr);
	mlx_destroy_image(data->mlx_ptr, data->ea.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->window);
	mlx_destroy_display(data->mlx_ptr);
	ft_exit(EXIT_SUCCESS);
	return (0);
}

int	key_events(int keycode, t_data *data)
{
	printf("keycode : %d\n", keycode);
	if (keycode == ESC)
	{
		win_close(data); //temp
	}
	// else if (keycode == W)
	// {
	// 	//...
	// }
	// else if (keycode == A)
	// {
	// 	//...
	// }
	// else if (keycode == S)
	// {
	// 	//...
	// }
	// else if (keycode == D)
	// {
	// 	//...
	// }
	// clear window
	// render
	return (0);
}

void	mlx_setup(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_exit(EXIT_FAILURE);
	data->window = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!data->window)
		ft_exit(EXIT_FAILURE);
	data->image.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->image.img_ptr)
		ft_exit(EXIT_FAILURE);
	data->image.img_data = mlx_get_data_addr(data->image.img_ptr, \
	&data->image.bpp, &data->image.size_line, &data->image.endian);
	if (!data->image.img_data)
		ft_exit(EXIT_FAILURE);
}

// void	images_init(t_image image)
// {
// 	image.img_ptr = NULL;
// 	image.img_data = NULL;
// 	image.img_path = NULL;
// }

// void	data_init(t_data *data)
// {
// 	images_init(data->image);
// 	images_init(data->no);
// 	images_init(data->so);
// 	images_init(data->we);
// 	images_init(data->ea);
// }

int main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		// data_init(&data);
		mlx_setup(&data);
		parse(&data, av[1]);
		// raycasting
		// mlx loop
		mlx_key_hook(data.window, key_events, &data);
		mlx_hook(data.window, CROSS_BUTTON, 0, win_close, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		write(2, "Error: missing map path\n", 24);
}
