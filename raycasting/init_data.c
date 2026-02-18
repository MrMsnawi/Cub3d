/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmardi <rmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:54:50 by rmardi            #+#    #+#             */
/*   Updated: 2025/11/09 12:13:04 by rmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	set_player_pos(t_data *data, int x, int y)
{
	data->pos_x = (double)x + 0.5;
	data->pos_y = (double)y + 0.5;
}

int	apply_orientation_1(t_data *data, char c)
{
	if (c == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = 0.66;
		data->plane_y = 0;
		return (1);
	}
	if (c == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -0.66;
		data->plane_y = 0;
		return (1);
	}
	return (0);
}

static int	apply_orientation(t_data *data, char c)
{
	if (1 == apply_orientation_1(data, c))
		return (1);
	if (c == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
		return (1);
	}
	if (c == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
		return (1);
	}
	return (0);
}

static int	find_player_start(t_data *data, int *px, int *py)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			c = data->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				*px = x;
				*py = y;
				set_player_pos(data, x, y);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	init_data(t_data *data)
{
	static int	initialized;
	int			px;
	int			py;
	char		c;

	if (initialized)
		return ;
	px = -1;
	py = -1;
	if (!find_player_start(data, &px, &py))
	{
		write(2, "Error: no player start\n", 23);
		ft_exit(1);
	}
	c = data->map[py][px];
	data->map[py][px] = '0';
	if (!apply_orientation(data, c))
	{
		write(2, "Error: wrong input\n", 19);
		ft_exit(1);
	}
	initialized = 1;
}
