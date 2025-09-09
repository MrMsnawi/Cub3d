/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:38:13 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/09 10:39:44 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

void	ft_exit(int	exit_status)
{
	ft_free();
	exit(exit_status);
}

int	key_events(int keycode, t_data *data)
{
	(void)data;
	if (keycode == ESC)
	{
		ft_exit(EXIT_SUCCESS); //temp
	}
	else if (keycode == W)
	{
		//...
	}
	else if (keycode == A)
	{
		//...
	}
	else if (keycode == S)
	{
		//...
	}
	else if (keycode == D)
	{
		//...
	}
	return (0);
}

int	win_close(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_ptr);
	mlx_destroy_window(data->mlx_ptr, data->window);
	ft_exit(EXIT_SUCCESS);
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
	// new image
	// get data addr
	// ...
	mlx_key_hook(data->window, key_events, data);
	mlx_hook(data->mlx_ptr, CROSS_BUTTON, 0, win_close, data);
}

int main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		mlx_setup(&data);
		// parse
		// raycasting
		// mlx loop
		mlx_loop(data.mlx_ptr);
		ft_free();
	}
	else
		write(2, "Error: missing map path\n", 24);
}
