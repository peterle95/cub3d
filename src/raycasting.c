/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:15:52 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/14 10:52:17 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	perform_dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		update_ray_position(ray);
		if (check_bounds(data, ray))
			break ;
		check_wall_collision(data, ray);
	}
	calculate_perpendicular_distance(ray);
}

void	render_frame(t_data *data)
{
	int				x;
	t_line_params	line;
	t_ray			ray;
	int				line_height;

	data->ray = &ray;
	x = 0;
	draw_floor_ceiling(data);
	while (x < data->window_width)
	{
		init_ray(&ray, data, x);
		calculate_step_and_side_dist(&ray);
		perform_dda(data, &ray);
		line_height = (int)(data->window_height / ray.perp_wall_dist);
		line.draw_start = -line_height / 2 + data->window_height / 2;
		if (line.draw_start < 0)
			line.draw_start = 0;
		line.draw_end = line_height / 2 + data->window_height / 2;
		if (line.draw_end >= data->window_height)
			line.draw_end = data->window_height - 1;
		line.x = x;
		line.ray = &ray;
		draw_textured_line(data, &line);
		x++;
	}
}

void	init_player_position(t_data *data)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			c = data->map.map_array[y][x];
			if (is_player_position(c))
			{
				set_player_position(data, x, y, c);
				return ;
			}
			x++;
		}
		y++;
	}
}
