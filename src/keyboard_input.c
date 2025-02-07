#include "cube3d.h"
#include <stdio.h>

int	key_up(int keycode, t_data *data)
{
	if (65307 == keycode)
		terminator(data);
	return (0);
}

int	key_down(int keycode, t_data *data)
{
	// Use WASD for movement.
	if (keycode == 'w' || keycode == 'W') // Move forward
	{
		printf("forward\n");
		player_move(data, UP);
	}
	if (keycode == 's' || keycode == 'S') // Move backward
	{
		printf("backward\n");
		player_move(data, DOWN);
	}
	if (keycode == 'a' || keycode == 'A') // Strafe left
	{
		printf("strafe left\n");
		move_player_strafe(data, -1);
	}
	if (keycode == 'd' || keycode == 'D') // Strafe right
	{
		printf("strafe right\n");
		move_player_strafe(data, 1);
	}
	return (0);
}
