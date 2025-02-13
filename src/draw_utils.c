/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:40:28 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 17:45:42 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_ceiling_values(t_data *data, t_ceiling *ceiling)
{
	ceiling->angle = atan2(data->player.dir_y, data->player.dir_x);
	ceiling->texture_offset = (int)((ceiling->angle / (2 * M_PI))
			* data->textures.img[CEILING].width)
		% data->textures.img[CEILING].width;
	if (ceiling->texture_offset < 0)
		ceiling->texture_offset += data->textures.img[CEILING].width;
}

int	calculate_sky_x(t_ceiling *ceiling, t_data *data)
{
	return ((ceiling->x + ceiling->texture_offset)
		% data->textures.img[CEILING].width);
}

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
