/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:57 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x
		* cos(angle) - data->player.dir_y * sin(angle);
	data->player.dir_y = old_dir_x
		* sin(angle) + data->player.dir_y * cos(angle);
	data->player.plane_x = data->player.plane_x
		* cos(angle) - data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x
		* sin(angle) + data->player.plane_y * cos(angle);
	data->player.angle += angle;
	if (data->player.angle > 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	else if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
}

void	move_player_direction(t_data *data, double direction)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_x
		* data->player.speed * direction;
	new_y = data->player.y + data->player.dir_y
		* data->player.speed * direction;
	if (data->map.map_array[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	move_player_strafe(t_data *data, double direction)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + (-data->player.dir_y)
		* data->player.speed * direction;
	new_y = data->player.y + (data->player.dir_x)
		* data->player.speed * direction;
	if (data->map.map_array[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

int	player_move(t_data *data, int dir)
{
	if (UP == dir)
		move_player_direction(data, 1);
	if (DOWN == dir)
		move_player_direction(data, -1);
	if (LEFT == dir)
		move_player_strafe(data, -1);
	if (RIGHT == dir)
		move_player_strafe(data, 1);
	return (0);
}
