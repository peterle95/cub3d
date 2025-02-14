/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_visualisation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:57:02 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 14:48:33 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	draw_raycast(t_data *data)
{
	t_line	*ray;

	ray = init_line(data->player.x * (data->scalar),
			data->player.y * (data->scalar),
			(int)(data->ray->map_x * (data->scalar)),
			(int)(data->ray->map_y * (data->scalar)));
	if (!ray)
	{
		error("Error: Failed to allocate memory for line.");
		return (1);
	}
	compute_line_points(data, ray);
	free(ray);
	return (0);
}
