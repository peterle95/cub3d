/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:15:52 by pmolzer           #+#    #+#             */
/*   Updated: 2025/01/28 13:43:34 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void draw_floor_ceiling(t_data *data)
{
    unsigned int ceiling = 0x87CEEB; // Default sky blue
    unsigned int floor = 0x8B4513;   // Default saddle brown

    for (int y = 0; y < data->window_height; y++)
    {
        if (y < data->window_height / 2)
        {
            for (int x = 0; x < data->window_width; x++)
                put_pixel_to_img(data, x, y, ceiling);
        }
        else
        {
            for (int x = 0; x < data->window_width; x++)
                put_pixel_to_img(data, x, y, floor);
        }
    }
}

void draw_textured_line(t_data *data, t_ray *ray, int x, int draw_start, int draw_end)
{
    // Add bounds checking for texture access
    int tex_num;
    if (ray->side == 0) {
        if (ray->ray_dir_x < 0) {
            tex_num = 3;  // West
        } else {
            tex_num = 2;  // East
        }
    } else {
        if (ray->ray_dir_y < 0) {
            tex_num = 0;  // North
        } else {
            tex_num = 1;  // South
        }
    }
    
    t_texture *tex = &data->textures.img[tex_num];
    
    // Add safety checks
    if (!tex || !tex->ptr || !tex->addr || tex->width <= 0 || tex->height <= 0)
    {
        // Fallback to solid color if texture is invalid
        int color = (ray->side == 1) ? 0x00FF0000 : 0x00CC0000;
        for (int y = draw_start; y < draw_end; y++)
            put_pixel_to_img(data, x, y, color);
        return;
    }

    // Rest of the function remains the same, starting from wall_x calculation
    double wall_x;
    if (ray->side == 0)
        wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    wall_x -= floor(wall_x);
    
    // Add bounds checking for texture coordinates
    int tex_x = (int)(wall_x * tex->width);
    tex_x = tex_x < 0 ? 0 : (tex_x >= tex->width ? tex->width - 1 : tex_x);

    double step = 1.0 * tex->height / (draw_end - draw_start);
    double tex_pos = (draw_start - data->window_height / 2 + (draw_end - draw_start) / 2) * step;

    for (int y = draw_start; y < draw_end; y++)
    {
        int tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        
        // Add bounds checking for pixel calculation
        if (tex_y >= 0 && tex_y < tex->height)
        {
            int pixel = (tex_y * tex->size_line) + (tex_x * (tex->bpp / 8));
            if (pixel >= 0 && pixel < (tex->size_line * tex->height))
            {
                unsigned int color = *(unsigned int*)(tex->addr + pixel);
                put_pixel_to_img(data, x, y, color);
            }
        }
    }
}

static void init_ray(t_ray *ray, t_data *data, int x)
{
    // Initialize ray position with player position
    ray->pos_x = data->player.x;
    ray->pos_y = data->player.y;
    
    // Calculate ray direction
    double camera_x = 2 * x / (double)data->window_width - 1;
    ray->ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
    ray->ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
    
    // Initialize map position
    ray->map_x = (int)ray->pos_x;
    ray->map_y = (int)ray->pos_y;
    
    // Calculate delta distances
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    
    ray->hit = 0;
}

void calculate_step_and_side_dist(t_ray *ray)
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

void perform_dda(t_data *data, t_ray *ray)
{
    printf("Starting DDA: pos=(%f,%f), dir=(%f,%f)\n",
           ray->pos_x, ray->pos_y,
           ray->ray_dir_x, ray->ray_dir_y);

    // Perform DDA (Digital Differential Analysis)
    while (ray->hit == 0)
    {
        // Jump to next map square
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }

        // Add bounds checking before accessing map_array
        if (ray->map_x < 0 || ray->map_y < 0 || 
            ray->map_y >= data->map.height || ray->map_x >= data->map.width)
        {
            ray->hit = 1;  // Hit boundary
            printf("Hit boundary at (%d,%d)\n", ray->map_x, ray->map_y);
            break;
        }

        // Check if ray has hit a wall
        if (data->map.map_array[ray->map_y][ray->map_x] == '1')
        {
            ray->hit = 1;
            printf("Hit wall at (%d,%d)\n", ray->map_x, ray->map_y);
        }
    }

    // Calculate distance projected on camera direction
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - ray->pos_x + 
            (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - ray->pos_y + 
            (1 - ray->step_y) / 2) / ray->ray_dir_y;

    printf("Final distance: %f\n", ray->perp_wall_dist);
}

void render_frame(t_data *data)
{
    draw_floor_ceiling(data);

    for (int x = 0; x < data->window_width; x++)
    {
        t_ray ray;
        init_ray(&ray, data, x);
        calculate_step_and_side_dist(&ray);
        perform_dda(data, &ray);

        // Calculate height of line to draw on screen
        int line_height = (int)(data->window_height / ray.perp_wall_dist);

        // Calculate lowest and highest pixel to fill in current stripe
        int draw_start = -line_height / 2 + data->window_height / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + data->window_height / 2;
        if (draw_end >= data->window_height)
            draw_end = data->window_height - 1;

        draw_textured_line(data, &ray, x, draw_start, draw_end);
    }
}

void init_player_position(t_data *data)
{
    // Find player position in map
    for (int y = 0; y < data->map.height; y++)
    {
        for (int x = 0; x < data->map.width; x++)
        {
            char c = data->map.map_array[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                // Set position (add 0.5 to place player in center of tile)
                data->player.x = x + 0.5;
                data->player.y = y + 0.5;
                
                // Set initial direction and plane based on spawn direction
                if (c == 'N') {
                    data->player.dir_x = 0; data->player.dir_y = -1;
                    data->player.plane_x = 0.66; data->player.plane_y = 0;
                }
                else if (c == 'S') {
                    data->player.dir_x = 0; data->player.dir_y = 1;
                    data->player.plane_x = -0.66; data->player.plane_y = 0;
                }
                else if (c == 'E') {
                    data->player.dir_x = 1; data->player.dir_y = 0;
                    data->player.plane_x = 0; data->player.plane_y = 0.66;
                }
                else if (c == 'W') {
                    data->player.dir_x = -1; data->player.dir_y = 0;
                    data->player.plane_x = 0; data->player.plane_y = -0.66;
                }
                return;
            }
        }
    }
}