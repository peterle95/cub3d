/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:22 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 13:42:52 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_img(t_data *data)
{
	data->img_data0 = malloc(sizeof(t_img_data));
	if (!data->img_data0)
	{
		error("Error: Failed to allocate memory for image data.");
		exit(EXIT_FAILURE);
	}
	data->img_data0->img = mlx_new_image(data->mlx,
			data->window_width, data->window_height);
	if (!data->img_data0->img)
	{
		free(data->img_data0);
		error("Error: Failed to create new image.");
		exit(EXIT_FAILURE);
	}
	data->img_data0->addr = mlx_get_data_addr(data->img_data0->img,
			&data->img_data0->bits_per_pixel,
			&data->img_data0->line_length, &data->img_data0->endian);
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
	unsigned int color = 0xFFFFFFFF;
	put_pixel_to_img(data, x, y, color);
}

void	add_random_pixels(t_data *data, int width, int height, int num_pixels)
{
    srand(time(NULL));
    for (int i = 0; i < num_pixels; i++) 
	{
        int x = rand() % width;
        int y = rand() % height;
        unsigned int color = (rand() % 0xFFFFFF) | 0xFF000000;
        put_pixel_to_img(data, x, y, color);
    }
}

// is this efficient? think about image buffering and limiting redraw
void	clear_image_to_colour(t_data *data, int colour)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->window_height)
	{
		x = 0;
		while (x < data->window_width)
		{
			put_pixel_to_img(data, x, y, colour);
			x++;
		}
		y++;
	}
}
