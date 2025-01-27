#include "cube3d.h"

int	key_up(int keycode, t_data *data)
{
	if (65307 == keycode)
		terminator(data);
	return (0);
}

int	key_down(int keycode, t_data *data)
{
	(void)data;
	if (0xff52 == keycode)
		printf("up\n");
	if (0xff54 == keycode)
		printf("down\n");
	if (0xff51 == keycode)
		printf("left\n");
	if (0xff53 == keycode)
		printf("right\n");
	return (0);
}
