/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:31:22 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 12:54:49 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int mouse_move(int x, int y, t_data *data)
{
    (void)y; // must remain here to match the MLX callback signature.
    int center_x;
    int center_y;
    int dx;
    double sensitivity;

    center_x = data->window_width / 2;
    center_y = data->window_height / 2;
    dx = x - center_x;
    sensitivity = 0.0001; // Lower sensitivity for slower rotation

    if (dx != 0)
        rotate_player(data, dx * sensitivity);

    // Warp the mouse pointer back to the center for continuous relative movement.
    mlx_mouse_move(data->mlx, data->mlx_win, center_x, center_y);
    return (0);
}

