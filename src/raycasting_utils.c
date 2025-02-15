/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:57:57 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_horizontal_line(t_data *data, int y, unsigned int color)
{
	int		x;

	x = 0;
	while (x < data->window_width)
	{
		put_pixel_to_img(data, x, y, color);
		x++;
	}
}

void	draw_floor_ceiling(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->window_height / 2)
	{
		if (!data->ceiling_loaded)
			draw_horizontal_line(data, y, data->map.ceiling_color);
		y++;
	}
	y = data->window_height / 2;
	while (y < data->window_height)
	{
		draw_horizontal_line(data, y, data->map.floor_color);
		y++;
	}
}

int	get_texture_number(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

void	draw_fallback_line(t_data *data, t_line_params *line)
{
	int		color;

	if (line->ray->side == 1)
		color = 0x00FF0000;
	else
		color = 0x00CC0000;
	while (line->draw_start < line->draw_end)
	{
		put_pixel_to_img(data, line->x, line->draw_start, color);
		line->draw_start++;
	}
}

double	calculate_wall_x(t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	return (wall_x - floor(wall_x));
}
