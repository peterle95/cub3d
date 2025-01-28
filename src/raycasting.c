/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:15:52 by pmolzer           #+#    #+#             */
/*   Updated: 2025/01/28 14:03:05 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void draw_floor_ceiling(t_data *data)
{
    unsigned int ceiling;
    unsigned int floor;
    int y;
    int x;

    ceiling = 0x87CEEB; // Default sky blue
    floor = 0x8B4513; // Default saddle brown
    y = 0;
    while (y < data->window_height)
    {
        if (y < data->window_height / 2)
        {
            x = 0;
            while (x < data->window_width)
            {
                put_pixel_to_img(data, x, y, ceiling);
                x++;
            }
        }
        else
        {
            x = 0;
            while (x < data->window_width)
            {
                put_pixel_to_img(data, x, y, floor);
                x++;
            }
        }
        y++;
    }
}

void draw_textured_line(t_data *data, t_ray *ray, int x, int draw_start, int draw_end)
{
    // Add bounds checking for texture access
    int tex_num;
    int y;
    double wall_x;
    int tex_x;
    int tex_y;
    double step;
    double tex_pos;
    int color;
    t_texture *tex;

    if (ray->side == 0) 
    {
        if (ray->ray_dir_x < 0) 
        {
            tex_num = 3;  // West
        } 
        else 
        {
            tex_num = 2;  // East
        }
    } 
    else 
    {
        if (ray->ray_dir_y < 0) 
        {
            tex_num = 0;  // North
        } 
        else 
        {
            tex_num = 1;  // South
        }
    }

    // Declare and initialize tex here
    tex = &data->textures.img[tex_num];

    // Add safety checks
    if (!tex || !tex->ptr || !tex->addr || tex->width <= 0 || tex->height <= 0)
    {
        // Fallback to solid color if texture is invalid
        color = (ray->side == 1) ? 0x00FF0000 : 0x00CC0000;
        y = draw_start;
        while (y < draw_end)
        {
            put_pixel_to_img(data, x, y, color);
            y++;
        }
        return;
    }

    // Rest of the function remains the same, starting from wall_x calculation
    if (ray->side == 0)
        wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    wall_x -= floor(wall_x);
    
    // Add bounds checking for texture coordinates
    tex_x = (int)(wall_x * tex->width);
    tex_x = tex_x < 0 ? 0 : (tex_x >= tex->width ? tex->width - 1 : tex_x);

    step = 1.0 * tex->height / (draw_end - draw_start);
    tex_pos = (draw_start - data->window_height / 2 + (draw_end - draw_start) / 2) * step;

    y = draw_start;
    while (y < draw_end)
    {
        tex_y = (int)tex_pos & (tex->height - 1);
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
        y++;
    }
}

static void init_ray(t_ray *ray, t_data *data, int x)
{
    double camera_x;
    // Initialize ray position with player position
    ray->pos_x = data->player.x;
    ray->pos_y = data->player.y;
    
    // Calculate ray direction
    camera_x = 2 * x / (double)data->window_width - 1;
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
    int x;
    int line_height;
    int draw_start;
    int draw_end;
    
    draw_floor_ceiling(data);
    x = 0;
    while (x < data->window_width)
    {
        t_ray ray;
        init_ray(&ray, data, x);
        calculate_step_and_side_dist(&ray);
        perform_dda(data, &ray);

        // Calculate height of line to draw on screen
        line_height = (int)(data->window_height / ray.perp_wall_dist);

        // Calculate lowest and highest pixel to fill in current stripe
        draw_start = -line_height / 2 + data->window_height / 2;
        if (draw_start < 0)
            draw_start = 0;
        draw_end = line_height / 2 + data->window_height / 2;
        if (draw_end >= data->window_height)
            draw_end = data->window_height - 1;

        draw_textured_line(data, &ray, x, draw_start, draw_end);
        x++;
    }
}

void init_player_position(t_data *data)
{
    int y;
    int x;
    char c;
    // Find player position in map
    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            c = data->map.map_array[y][x];
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
            x++;
        }
        y++;
    }
}