/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:11:37 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 15:12:06 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	init_data(t_data *data)
{
	data->map.map_array = NULL;
	data->window_width = 1920;
	data->window_height = 1080;
	// Initialize player position and direction, to be updated with map data
	data->player.x = 22;  // Starting position
	data->player.y = 12;
	data->player.dir_x = -1;  // Initial direction vector
	data->player.dir_y = 0;
	data->player.plane_x = 0;  // Camera plane
	data->player.plane_y = 0.66; // FOV is about 66 degrees
	return (0);
}

int	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 3, 1L << 1, key_up, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_down, data);
	mlx_hook(data->mlx_win, ClientMessage, 0, close_window, data);
	mlx_mouse_hook(data->mlx_win, mouse_mv, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, draw, data);
	return (0);
}

// seems as though the player speed must divide into some value
// for the walls to render correctly
int	init_player(t_data *data)
{
	data->player.x = 0;
	data->player.y = 0;
	data->player.speed = 0.5;
	data->player.rotation_speed = 0.1;
	data->player.angle = 0.0;
	return (0);
}
