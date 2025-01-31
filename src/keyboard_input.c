#include "cube3d.h"

int	key_up(int keycode, t_data *data)
{
	if (65307 == keycode)
		terminator(data);
	return (0);
}

int	key_down(int keycode, t_data *data)
{
	// change movement to WASD, while left and right arrow are used for rotation
	(void)data;
	if (keycode == 'w' || keycode == 'W') // Move up
	{
		printf("up\n");
		player_move(data, UP);
	}
	if (keycode == 's' || keycode == 'S') // Move down
	{
		printf("down\n");
		player_move(data, DOWN);
	}
	if (keycode == 'a' || keycode == 'A') // Move left
	{
		printf("left\n");
		player_move(data, LEFT);
	}
	if (keycode == 'd' || keycode == 'D') // Move right
	{
		printf("right\n");
		player_move(data, RIGHT);
	}
	return (0);
}
