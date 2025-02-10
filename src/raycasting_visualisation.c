/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_visualisation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:57:02 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/10 11:18:50 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	draw_raycast(t_data *data)
{
	t_line	*ray;
	// printf("%d - %d - %f - %f\n", (int)data->player.x, (int)data->player.y,
	// 		data->ray->pos_x, data->ray->pos_y);
	//
	ray = init_line(data->player.x * (data->scalar), data->player.y * (data->scalar),
			(int)(data->ray->map_x * (data->scalar)), (int)(data->ray->map_y * (data->scalar)));
	compute_line_points(data, ray);
	return (0);	
}

