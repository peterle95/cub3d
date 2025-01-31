#include "cube3d.h"

static void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x = data->player.dir_x;
	double	old_plane_x = data->player.plane_x;

	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y * sin(angle);
	data->player.dir_y = old_dir_x * sin(angle) + data->player.dir_y * cos(angle);
	data->player.plane_x = data->player.plane_x * cos(angle) - data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x * sin(angle) + data->player.plane_y * cos(angle);
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
	if (UP == dir)
		move_player_direction(data, 1);
	if (DOWN == dir)
		move_player_direction(data, -1);
	if (LEFT == dir)
		rotate_player(data, -(data->player.speed));
	if (RIGHT == dir)
		rotate_player(data, (data->player.speed));
	return (0);
}

