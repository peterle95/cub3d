/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:15:52 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/04 11:30:22 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// static void draw_ceiling(t_data *data) // unsigned int ceiling_color)
// {
// 	int	y;
// 	int	x;
// 	int pixel;
// 	int color;
//
// 	y = 0;
// 	while (y < data->window_height / 2)
// 	{
// 		x = 0;
// 		while (x < data->window_width)
// 		{
// 			pixel = (y * data->textures.img[2].size_line) + (x * (data->textures.img[2].bpp / 8));
// 			color = *(int *)(data->textures.img[2].addr + pixel);
// 			if (color != 0xFFFFFF)
// 				mlx_pixel_put(data->mlx, data->mlx_win, 0 + x, 0 + y, color);
// 			x++;
// 		}
// 		y++;
// 	}
//     // int y;
//     //
//     // y = 0;
//     // while (y < data->window_height / 2)
//     // {
//     //     draw_horizontal_line(data, y, ceiling_color);
//     //     y++;
//     // }
// }

int	get_texture_number(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return 1;  // West
		else
			return 1;  // East
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return 1;  // North
		else
			return (1);  // South
	}
}

double	calculate_wall_x(t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	return (wall_x - floor(wall_x));
}

int calculate_tex_x(t_ray *ray, t_texture *tex)
{
    double wall_x;
    int tex_x;

    wall_x = calculate_wall_x(ray);
    tex_x = (int)(wall_x * tex->width);
    if (tex_x < 0)
        return (0);
    if (tex_x >= tex->width)
        return (tex->width - 1);
    return (tex_x);
}

void calculate_step_pos(t_data *data, t_line_params *line, t_texture *tex, double step_pos[2])
{
    step_pos[0] = 1.0 * tex->height / (line->draw_end - line->draw_start);
    step_pos[1] = (line->draw_start - data->window_height / 2 
                  + (line->draw_end - line->draw_start) / 2) * step_pos[0];
}

void	init_ray(t_ray *ray, t_data *data, int x)
{
	double	camera_x;

	ray->pos_x = data->player.x;
	ray->pos_y = data->player.y;
	camera_x = 2 * x / (double)data->window_width - 1;
	ray->ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	ray->ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y; 
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	calculate_step_and_side_dist(t_ray *ray)
{
    // Calculate step direction and initial side distance
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}
