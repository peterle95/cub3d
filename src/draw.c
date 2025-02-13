/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:10:00 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/09 11:38:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	render_with_transparency(t_data *data, t_texture *t, int img_x, int img_y)
{
	int	y;
	int	x;
	int	pixel;
	int	color;

	y = 0;
	while (y < t->height)
	{
		x = 0;
		while (x < t->width)
		{
			pixel = (y * t->size_line) + (x * (t->bpp / 8));
			color = *(int *)(t->addr + pixel);
			if (color != 0xFFFFFF)
				mlx_pixel_put(data->mlx, data->mlx_win,
					img_x + x, img_y + y, color);
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_player_position(t_data *data)
{
	int	centre_x;
	int	centre_y;

	centre_x = data->textures.img[0].width / 2;
	centre_y = data->textures.img[0].height / 2;
	render_with_transparency(data, &data->textures.img[0],
		(data->player.x * data->scalar) + data->offset - centre_x,
		(data->player.y * data->scalar) + data->offset - centre_y);
	return (0);
}

int	draw(t_data *data)
{
	clear_image_to_colour(data, set_trgb(data->t, data->r, data->g, data->b));
	if (data->ceiling_loaded)
		draw_ceiling(data);
	render_frame(data);
	draw_grid(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->img_data0->img, 0, 0);
	if (data->r > 0)
		data->r--;
	return (0);
}

void	draw_ceiling(t_data *data)
{
	t_ceiling	c;

	c.angle = atan2(data->player.dir_y, data->player.dir_x);
	c.texture_offset = (int)((c.angle / (2 * M_PI))
			* data->textures.img[CEILING].width)
		% data->textures.img[CEILING].width;
	if (c.texture_offset < 0)
		c.texture_offset += data->textures.img[CEILING].width;
	c.y = 0;
	while (c.y < data->window_height / 2)
	{
		c.x = 0;
		while (c.x < data->window_width)
		{
			c.sky_x = (c.x + c.texture_offset)
				% data->textures.img[CEILING].width;
			c.pixel = (c.y * data->textures.img[CEILING].size_line) + (c.sky_x
					* (data->textures.img[CEILING].bpp / 8));
			c.color = *(int *)(data->textures.img[CEILING].addr + c.pixel);
			if (c.color != 0xFFFFFF)
				put_pixel_to_img(data, c.x, c.y, c.color);
			c.x++;
		}
		c.y++;
	}
}
