/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:16:45 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/04 12:05:19 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_ray_position(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	calculate_perpendicular_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + 
			(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + 
			(1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	perform_dda(t_data *data, t_ray *ray)
{
	printf("Starting DDA: pos=(%f,%f), dir=(%f,%f)\n",
		ray->pos_x, ray->pos_y,
		ray->ray_dir_x, ray->ray_dir_y);
	while (ray->hit == 0)
	{
		update_ray_position(ray);
		if (check_bounds(data, ray))
			break;
		check_wall_collision(data, ray);
	}
	calculate_perpendicular_distance(ray);
	printf("Final distance: %f\n", ray->perp_wall_dist);
}

void	render_frame(t_data *data)
{
	int		x;
	t_line_params	line;
	t_ray	ray;
	int		line_height;

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