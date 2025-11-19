/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmardi <rmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:38:13 by abmasnao          #+#    #+#             */
/*   Updated: 2025/11/10 11:28:57 by rmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

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

static void	rotate_view(t_data *data, double ang)
{
	double	ca;
	double	sa;
	double	old_dir_x;
	double	old_plane_x;

	ca = cos(ang);
	sa = sin(ang);
	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	data->dir_x = data->dir_x * ca - data->dir_y * sa;
	data->dir_y = old_dir_x * sa + data->dir_y * ca;
	data->plane_x = data->plane_x * ca - data->plane_y * sa;
	data->plane_y = old_plane_x * sa + data->plane_y * ca;
}

static int	is_blocked(t_data *data, int yy, int xx)
{
	if (yy < 0 || xx < 0)
		return (1);
	if (!data->map[yy])
		return (1);
	if (!data->map[yy][xx])
		return (1);
	if (data->map[yy][xx] == ' ')
		return (1);
	return (data->map[yy][xx] == '1');
}

static void	try_move(t_data *data, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = data->pos_x + dx;
	ny = data->pos_y + dy;
	if (!is_blocked(data, (int)data->pos_y, (int)nx))
		data->pos_x = nx;
	if (!is_blocked(data, (int)ny, (int)data->pos_x))
		data->pos_y = ny;
}

static int	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->keys.a)
		rotate_view(data, -ROT_SPEED);
	if (data->keys.d)
		rotate_view(data, ROT_SPEED);
	if (data->keys.up || data->keys.w)
		try_move(data, data->dir_x * MOVE_SPEED, data->dir_y * MOVE_SPEED);
	if (data->keys.down || data->keys.s)
		try_move(data, -data->dir_x * MOVE_SPEED, -data->dir_y * MOVE_SPEED);
	if (data->keys.right)
		try_move(data, -data->dir_y * MOVE_SPEED, data->dir_x * MOVE_SPEED);
	if (data->keys.left)
		try_move(data, data->dir_y * MOVE_SPEED, -data->dir_x * MOVE_SPEED);
	raycasting(data);
	return (0);
}

static int	on_keydown(int keycode, t_data *data)
{
	if (keycode == ESC)
		return (win_close(data));
	if (keycode == A)
		data->keys.a = 1;
	if (keycode == D)
		data->keys.d = 1;
	if (keycode == W)
		data->keys.w = 1;
	if (keycode == S)
		data->keys.s = 1;
	if (keycode == LEFT)
		data->keys.left = 1;
	if (keycode == RIGHT)
		data->keys.right = 1;
	if (keycode == UP)
		data->keys.up = 1;
	if (keycode == DOWN)
		data->keys.down = 1;
	return (0);
}

static int	on_keyup(int keycode, t_data *data)
{
	if (keycode == A)
		data->keys.a = 0;
	if (keycode == D)
		data->keys.d = 0;
	if (keycode == W)
		data->keys.w = 0;
	if (keycode == S)
		data->keys.s = 0;
	if (keycode == LEFT)
		data->keys.left = 0;
	if (keycode == RIGHT)
		data->keys.right = 0;
	if (keycode == UP)
		data->keys.up = 0;
	if (keycode == DOWN)
		data->keys.down = 0;
	return (0);
}

void	mlx_setup(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_exit(EXIT_FAILURE);
	data->image.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->image.img_ptr)
		ft_exit(EXIT_FAILURE);
	data->image.img_data = mlx_get_data_addr(data->image.img_ptr, \
	&data->image.bpp, &data->image.size_line, &data->image.endian);
	if (!data->image.img_data)
		ft_exit(EXIT_FAILURE);
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.w = 0;
	data->keys.s = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	data->keys.up = 0;
	data->keys.down = 0;
}

void	mlx_listens(t_data *data)
{
	mlx_hook(data->window, 2, 1L << 0, on_keydown, data);
	mlx_hook(data->window, 3, 1L << 1, on_keyup, data);
	mlx_hook(data->window, CROSS_BUTTON, 0, win_close, data);
	mlx_loop_hook(data->mlx_ptr, game_loop, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	set_data_ptr(data);
	if (ac == 2)
	{
		mlx_setup(data);
		parse(data, av[1]);
		data->window = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3D");
		if (!data->window)
			ft_exit(EXIT_FAILURE);
		raycasting(data);
		mlx_listens(data);
	}
	else
		write(2, "Error: Usage: ./cude3D ./path_to_map\n", 37);
}
