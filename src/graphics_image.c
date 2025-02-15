/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:22 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_img(t_data *data)
{
	data->img_data0 = malloc(sizeof(t_img_data));
	if (!data->img_data0)
	{
		error("Failed to allocate memory for image data", ENOMEM);
		terminator(data, EXIT_FAILURE);
	}
	data->img_data0->img = mlx_new_image(data->mlx,
			data->window_width, data->window_height);
	if (!data->img_data0->img)
	{
		error("Failed to create new image", EFAULT);
		terminator(data, EXIT_FAILURE);
	}
	data->img_data0->addr = mlx_get_data_addr(data->img_data0->img,
			&data->img_data0->bits_per_pixel,
			&data->img_data0->line_length,
			&data->img_data0->endian);
	if (!data->img_data0->addr)
	{
		error("Failed to get image data address", EFAULT);
		terminator(data, EXIT_FAILURE);
	}
}

void	put_pixel_to_img(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < data->window_width && y >= 0 && y < data->window_height)
	{
		dst = data->img_data0->addr + (y * data->img_data0->line_length + x
				* (data->img_data0->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

void	add_pixels(t_data *data, int x, int y)
{
	unsigned int	color;

	color = 0xFFFFFFFF;
	put_pixel_to_img(data, x, y, color);
}

void	clear_image_to_colour(t_data *data, int colour)
{
	int	total_pixels;
	int	*img_buffer;
	int	i;

	total_pixels = data->window_width * data->window_height;
	img_buffer = (int *)data->img_data0->addr;
	i = 0;
	while (i < total_pixels)
	{
		img_buffer[i] = colour;
		i++;
	}
}
