/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmardi <rmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:12:43 by rmardi            #+#    #+#             */
/*   Updated: 2025/11/09 12:42:48 by rmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/include/cub.h"

void	init_sides_steps(t_raycasting_data *rd, t_data *data)
{
	if (rd->raydir_x < 0)
	{
		rd->step_x = -1;
		rd->side_x = (data->pos_x - rd->map_x)
			* rd->delta_x;
	}
	else
	{
		rd->step_x = 1;
		rd->side_x = (rd->map_x + 1 - data->pos_x)
			* rd->delta_x;
	}
	if (rd->raydir_y < 0)
	{
		rd->step_y = -1;
		rd->side_y = (data->pos_y - rd->map_y)
			* rd->delta_y;
	}
	else
	{
		rd->step_y = 1;
		rd->side_y = (rd->map_y + 1 - data->pos_y)
			* rd->delta_y;
	}
}

void	init_raycasting(t_raycasting_data *rd, int x, t_data *data)
{
	init_data(data);
	rd->cam_x = 2 * x / (double)WIDTH - 1;
	rd->raydir_x = data->dir_x + data->plane_x * rd->cam_x;
	rd->raydir_y = data->dir_y + data->plane_y * rd->cam_x;
	rd->map_x = (int)data->pos_x;
	rd->map_y = (int)data->pos_y;
	rd->delta_x = fabs(1 / rd->raydir_x);
	rd->delta_y = fabs(1 / rd->raydir_y);
	rd->hit = 0;
	init_sides_steps(rd, data);
}

void	perform_dda(t_raycasting_data *rd, t_data *data)
{
	while (rd->hit == 0)
	{
		if (rd->side_x < rd->side_y)
		{
			rd->side_x += rd->delta_x;
			rd->map_x += rd->step_x;
			rd->side = 0;
		}
		else
		{
			rd->side_y += rd->delta_y;
			rd->map_y += rd->step_y;
			rd->side = 1;
		}
		if (data->map[rd->map_y][rd->map_x] == '1')
			rd->hit = 1;
	}
}

void	cal_dist(t_raycasting_data *rd)
{
	if (rd->side == 0)
		rd->p_w_d = rd->side_x - rd->delta_x;
	else
		rd->p_w_d = rd->side_y - rd->delta_y;
	rd->line_height = (int)(HEIGHT / rd->p_w_d);
	rd->draw_start = -(rd->line_height) / 2 + HEIGHT / 2;
	if (rd->draw_start < 0)
		rd->draw_start = 0;
	rd->draw_end = rd->line_height / 2 + HEIGHT / 2;
	if (rd->draw_end >= HEIGHT)
		rd->draw_end = HEIGHT - 1;
}

void	put_pixel_img(t_image *img, int x, int y, int color)
{
	char	*p;

	if (!img)
		return ;
	if ((unsigned)x >= WIDTH || (unsigned)y >= HEIGHT)
		return ;
	p = img->img_data + y * img->size_line + x * (img->bpp / 8);
	*(unsigned int *)p = (unsigned int)color;
}

void	draw_textures_floor(t_raycasting_data *rd, t_data *data, int *y, int *x)
{
	while (*y <= rd->draw_end)
	{
		rd->tex_y = (int)rd->texpos;
		rd->src = rd->tex->img_data + rd->tex_y * rd->tex->size_line
			+ rd->tex_x * rd->bpp_bytes;
		rd->color = *(unsigned int *)rd->src;
		if (rd->side == 1)
			rd->color = ((rd->color >> 1) & 0x7F7F7F);
		put_pixel_img(&data->image, *x, *y, (int)rd->color);
		rd->texpos = rd->texpos + rd->step;
		(*y)++;
	}
	while (*y < HEIGHT)
	{
		put_pixel_img(&data->image, *x, *y, data->f);
		(*y)++;
	}
}

void	init_tex(t_raycasting_data *rd, t_data *data)
{
	rd->tex = &data->so;
	if (rd->tex->img_ptr != NULL && rd->tex->img_data == NULL)
		rd->tex->img_data = mlx_get_data_addr(rd->tex->img_ptr, &rd->tex->bpp,
				&rd->tex->size_line, &rd->tex->endian);
}

void	draw_line(t_raycasting_data *rd, t_data *data, int x)
{
	int	y;

	y = 0;
	init_tex(rd, data);
	rd->bpp_bytes = rd->tex->bpp / 8;
	while (y < rd->draw_start)
	{
		put_pixel_img(&data->image, x, y, data->c);
		y++;
	}
	if (rd->side == 0)
		rd->wallx = data->pos_y + rd->p_w_d * rd->raydir_y;
	else
		rd->wallx = data->pos_x + rd->p_w_d * rd->raydir_x;
	rd->wallx -= (int)rd->wallx;
	rd->tex_x = (int)(rd->wallx * (double)rd->tex->width);
	if (rd->side == 0 && rd->raydir_x > 0)
		rd->tex_x = rd->tex->width - rd->tex_x - 1;
	if (rd->side == 1 && rd->raydir_y < 0)
		rd->tex_x = rd->tex->width - rd->tex_x - 1;
	rd->step = (double)rd->tex->height / (double)rd->line_height;
	rd->texpos = (rd->draw_start - HEIGHT / 2.0 + rd->line_height / 2.0)
		* rd->step;
	draw_textures_floor(rd, data, &y, &x);
}

void	raycasting(t_data *data)
{
	int					x;
	t_raycasting_data	ray_data;

	x = 0;
	while (x < WIDTH)
	{
		init_raycasting(&ray_data, x, data);
		perform_dda(&ray_data, data);
		cal_dist(&ray_data);
		draw_line(&ray_data, data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->window,
		data->image.img_ptr, 0, 0);
}
