/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:11:37 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/10 11:39:01 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	init_data(t_data *data)
{
	data->map.map_array = NULL;
	data->window_width = 1920;
	data->window_height = 1080;
	data->player.x = 0;
	data->player.y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	return (0);
}

int	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 3, KEY_RELEASE, key_up, data);
	mlx_hook(data->mlx_win, 2, KEY_PRESS, key_down, data);
	mlx_hook(data->mlx_win, ClientMessage, 0, close_window, data);
	mlx_hook(data->mlx_win, 6, POINTER_MOTION, mouse_move, data);
	mlx_loop_hook(data->mlx, draw, data);
	return (0);
}

int	init_player(t_data *data)
{
	data->player.x = 0;
	data->player.y = 0;
	data->player.speed = 0.5;
	data->player.rotation_speed = 0.1;
	data->player.angle = 0.0;
	return (0);
}
