#include "cube3d.h"

static void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x; 
	double	old_plane_x; 
	
	old_dir_x	= data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y * sin(angle);
	data->player.dir_y = old_dir_x * sin(angle) + data->player.dir_y * cos(angle);	
	data->player.plane_x = data->player.plane_x * cos(angle) - data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x * sin(angle) + data->player.plane_y * cos(angle);
	// update player angle for rotating skybox
	data->player.angle += angle;
    // keep angle within 0 - 2π (360 degrees)
	if (data->player.angle > 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	else if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
}

void	move_player_direction(t_data *data, double direction)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_x * data->player.speed * direction;
	new_y = data->player.y + data->player.dir_y * data->player.speed * direction;
	data->player.y = new_y;
	data->player.x = new_x;
}

int	player_move(t_data *data, int dir)
{
 //     // Check if new position is within map bounds
 //    if (data->player.x < 0 || data->player.x >= data->map.width || data->player.y < 0 || data->player.y >= data->map.height)
 //        return (0);
	//
 //    // Check if new position is not a wall
 //    if (data->map.map_array[(int)data->player.y][(int)data->player.x] != '1') 
	// {
 //        data->player.x = data->player.x;
 //        data->player.y = data->player.y;
 //    }

	if (UP == dir)
		move_player_direction(data, 1);
	if (DOWN == dir)
		move_player_direction(data, -1);
	if (LEFT == dir)
	{
		rotate_player(data, -(data->player.rotation_speed));
		// data->player.angle -= 100;
	}
	if (RIGHT == dir)
	{
		rotate_player(data, (data->player.rotation_speed));
		// data->player.angle += 100;
	}
	return (0);
}

