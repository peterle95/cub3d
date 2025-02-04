/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:05:15 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/04 11:13:39 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	set_player_direction_ns(t_data *data, char direction)
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

static void	set_player_direction_ew(t_data *data, char direction)
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

static void	set_player_direction(t_data *data, char direction)
{ 
	if(direction == 'N' || direction == 'S') 
		set_player_direction_ns(data, direction);
	else if (direction == 'E' || direction == 'W')
		set_player_direction_ew(data, direction);
}

static int	is_player_position(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player_position(t_data *data, int x, int y, char direction)
{
    // Set position (add 0.5 to place player in center of tile)
	data->player.x = x + 0.5;
	data->player.y = y + 0.5;
	set_player_direction(data, direction);
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