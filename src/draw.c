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
	int pixel;
	int color;

	y = 0;
	while (y < t->height)
	{
		x = 0;
		while (x < t->width)
		{
			pixel = (y * t->size_line) + (x * (t->bpp / 8));
			color = *(int *)(t->addr + pixel);
			if (color != 0xFFFFFF)
				mlx_pixel_put(data->mlx, data->mlx_win, img_x + x, img_y + y, color);
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
	// draw player position
	render_with_transparency(data, &data->textures.img[0],
			(data->player.x * data->scalar)+ data->offset - centre_x,
			(data->player.y * data->scalar) + data->offset - centre_y);
	return (0);
}

// TODO: buffered images
int	draw(t_data *data)
{
	clear_image_to_colour(data, set_trgb(data->t, data->r, data->g, data->b));


	// Render the 3D view
	render_frame(data);

	// draw mini map
	draw_grid(data);
	// draw_player_position(data);

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_data0->img, 0, 0);	
	if (data->r > 0)
		data->r--;
	return (0);
}
