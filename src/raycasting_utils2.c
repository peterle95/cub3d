/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:07:14 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:07:15 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_texture_pixel(t_data *data, t_texture *tex,
		int params[4], double tex_pos)
{
	int				tex_y;
	int				pixel;
	unsigned int	color;

	tex_y = (int)tex_pos & (tex->height - 1);
	if (tex_y >= 0 && tex_y < tex->height)
	{
		pixel = (tex_y * tex->size_line) + (params[2] * (tex->bpp / 8));
		if (pixel >= 0 && pixel < (tex->size_line * tex->height))
		{
			color = *(unsigned int *)(tex->addr + pixel);
			put_pixel_to_img(data, params[0], params[1], color);
		}
	}
}

int	calculate_tex_x(t_ray *ray, t_texture *tex)
{
	double	wall_x;
	int		tex_x;

	wall_x = calculate_wall_x(ray);
	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		return (0);
	if (tex_x >= tex->width)
		return (tex->width - 1);
	return (tex_x);
}

void	calculate_step_pos(t_data *data, t_line_params *line,
		t_texture *tex, double step_pos[2])
{
	step_pos[0] = 1.0 * tex->height / (line->draw_end - line->draw_start);
	step_pos[1] = (line->draw_start - data->window_height / 2
			+ (line->draw_end - line->draw_start) / 2) * step_pos[0];
}

void	draw_textured_line(t_data *data, t_line_params *line)
{
	t_texture	*tex;
	double		step_pos[2];
	int			params[4];
	int			y;

	tex = &data->textures.img[get_texture_number(line->ray)];
	if (!tex || !tex->ptr || !tex->addr || tex->width <= 0 || tex->height <= 0)
	{
		draw_fallback_line(data, line);
		return ;
	}
	params[0] = line->x;
	params[2] = calculate_tex_x(line->ray, tex);
	calculate_step_pos(data, line, tex, step_pos);
	y = line->draw_start;
	while (y < line->draw_end)
	{
		params[1] = y;
		draw_texture_pixel(data, tex, params, step_pos[1]);
		step_pos[1] += step_pos[0];
		y++;
	}
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
