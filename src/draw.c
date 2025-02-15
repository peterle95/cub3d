/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:10:00 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw(t_data *data)
{
	clear_image_to_colour(data, 0x000000);
	if (data->ceiling_loaded)
		draw_ceiling(data);
	render_frame(data);
	draw_grid(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->img_data0->img, 0, 0);
	return (0);
}

static int	get_ceiling_pixel(t_ceiling *ceiling, t_data *data)
{
	return ((ceiling->y * data->textures.img[CEILING].size_line)
		+ (ceiling->sky_x * (data->textures.img[CEILING].bpp / 8)));
}

static void	draw_ceiling_line(t_data *data, t_ceiling *ceiling)
{
	ceiling->x = 0;
	while (ceiling->x < data->window_width)
	{
		ceiling->sky_x = calculate_sky_x(ceiling, data);
		ceiling->pixel = get_ceiling_pixel(ceiling, data);
		ceiling->color = *(int *)(data->textures.img[CEILING].addr
				+ ceiling->pixel);
		if (ceiling->color != 0xFFFFFF)
			put_pixel_to_img(data, ceiling->x, ceiling->y, ceiling->color);
		ceiling->x++;
	}
}

void	draw_ceiling(t_data *data)
{
	t_ceiling	ceiling;

	if (data->textures.img[CEILING].width <= 0)
		return ;
	init_ceiling_values(data, &ceiling);
	ceiling.y = 0;
	while (ceiling.y < data->window_height / 2)
	{
		draw_ceiling_line(data, &ceiling);
		ceiling.y++;
	}
}
