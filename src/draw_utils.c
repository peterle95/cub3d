/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:03:35 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/04 12:04:12 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void calculate_step_pos(t_data *data, t_line_params *line, t_texture *tex, double step_pos[2])
{
    step_pos[0] = 1.0 * tex->height / (line->draw_end - line->draw_start);
    step_pos[1] = (line->draw_start - data->window_height / 2 
                  + (line->draw_end - line->draw_start) / 2) * step_pos[0];
}

void	draw_horizontal_line(t_data *data, int y, unsigned int color)
{
	int		x;

	x = 0;
	while (x < data->window_width)
	{
		put_pixel_to_img(data, x, y, color);
		x++;
	}
}

void	draw_floor(t_data *data, unsigned int floor_color)
{
	int		y;

	y = data->window_height / 2;
	while (y < data->window_height)
	{
		draw_horizontal_line(data, y, floor_color);
		y++;
	}
}

void	draw_floor_ceiling(t_data *data)
{
    // unsigned int ceiling;
    unsigned int floor;

    // change this to actual texture
    // ceiling = 0x87CEEB;
    floor = 0x8B4513;
    // draw_ceiling(data); //, ceiling);
    draw_floor(data, floor);
}