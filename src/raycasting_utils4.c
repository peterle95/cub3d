/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:07:21 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:07:22 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_player_direction_ns(t_data *data, char direction)
{
	if (direction == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (direction == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
}

void	set_player_direction_ew(t_data *data, char direction)
{
	if (direction == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

void	set_player_direction(t_data *data, char direction)
{
	if (direction == 'N' || direction == 'S')
		set_player_direction_ns(data, direction);
	else if (direction == 'E' || direction == 'W')
		set_player_direction_ew(data, direction);
}

int	is_player_position(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_position(t_data *data, int x, int y, char direction)
{
	data->player.x = x + 0.5;
	data->player.y = y + 0.5;
	set_player_direction(data, direction);
}
