/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:27:04 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/04 11:30:45 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


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

static void	draw_fallback_line(t_data *data, t_line_params *line)
{
	int		color;

    // change this to actual texture 
   if (line->ray->side == 1)
        color = 0x00FF0000;
    else
        color = 0x00CC0000;
    while (line->draw_start < line->draw_end)
    {
        put_pixel_to_img(data, line->x, line->draw_start, color);
        line->draw_start++;
    }
}

static void	draw_texture_pixel(t_data *data, t_texture *tex, int params[4], double tex_pos)
{
	int		tex_y;
	int		pixel;
	unsigned int	color;


	tex_y = (int)tex_pos & (tex->height - 1);
	if (tex_y >= 0 && tex_y < tex->height)
	{
		pixel = (tex_y * tex->size_line) + (params[2] * (tex->bpp / 8));
		if (pixel >= 0 && pixel < (tex->size_line * tex->height))
		{
			color = *(unsigned int*)(tex->addr + pixel);
			put_pixel_to_img(data, params[0], params[1], color);
		}
	}
}

void draw_textured_line(t_data *data, t_line_params *line)
{
    t_texture *tex;
    double step_pos[2];
    int params[4];
    
    tex = &data->textures.img[get_texture_number(line->ray)];
    if (!tex || !tex->ptr || !tex->addr || tex->width <= 0 || tex->height <= 0)
    {
        draw_fallback_line(data, line);
        return;
    }

    params[0] = line->x;
    params[2] = calculate_tex_x(line->ray, tex);
    calculate_step_pos(data, line, tex, step_pos);

    for (int y = line->draw_start; y < line->draw_end; y++)
    {
        params[1] = y;
        draw_texture_pixel(data, tex, params, step_pos[1]);
	step_pos[1] += step_pos[0];
	}
}