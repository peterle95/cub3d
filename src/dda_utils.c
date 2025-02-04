/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:04:51 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/04 12:05:23 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calculate_step_and_side_dist(t_ray *ray)
{
    // Calculate step direction and initial side distance
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

int	check_bounds(t_data *data, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_y < 0 || 
		ray->map_y >= data->map.height || ray->map_x >= data->map.width)
	{
		ray->hit = 1;  // Hit boundary
		printf("Hit boundary at (%d,%d)\n", ray->map_x, ray->map_y);
		return (1);
	}   
	return (0);
}

void	check_wall_collision(t_data *data, t_ray *ray)
{
    if (data->map.map_array[ray->map_y][ray->map_x] == '1')
    {
		draw_raycast(data);
        ray->hit = 1;
        printf("Hit wall at (%d,%d)\n", ray->map_x, ray->map_y);
    }
}