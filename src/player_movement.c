#include "cube3d.h"

int	player_move(t_data *data, int dir)
{
	if (UP == dir)
		data->player.y--;
	if (DOWN == dir)
		data->player.y++;
	if (LEFT == dir)
		data->player.x--;
	if (RIGHT == dir)
		data->player.x++;
	return (0);
}
