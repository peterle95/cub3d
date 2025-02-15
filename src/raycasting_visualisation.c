/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_visualisation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:57:02 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_raycast(t_data *data)
{
	t_line	*ray;

	ray = init_line(data->player.x * (data->scalar),
			data->player.y * (data->scalar),
			(int)(data->ray->map_x * (data->scalar)),
			(int)(data->ray->map_y * (data->scalar)));
	if (!ray)
	{
		error("Failed to allocate memory for line", errno);
		return (1);
	}
	compute_line_points(data, ray);
	free(ray);
	return (0);
}
