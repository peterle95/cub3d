#include "cube3d.h"

int	draw_raycast(t_data *data)
{
	t_line	*ray;
	// printf("%d - %d - %f - %f\n", (int)data->player.x, (int)data->player.y,
	// 		data->ray->pos_x, data->ray->pos_y);
	//
	ray = init_line(data->player.x * (data->scalar), data->player.y * (data->scalar),
			(int)(data->ray->map_x * (data->scalar)), (int)(data->ray->map_y * (data->scalar)));
	compute_line_points(data, ray);
	return (0);	
}

