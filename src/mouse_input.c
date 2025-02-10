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

static int ignore_next_warp = 0;

int mouse_move(int x, int y, t_data *data)
{
	(void)y;
    int center_x;
    int center_y;
    int dx;
    double sensitivity;

	// if the last event was caused by warping, ignore this event
	// otherwise infinite loop of warp, call, warp, call, ...
    if (ignore_next_warp)
	{
        ignore_next_warp = 0;
        return (0);
    }

    center_x = data->window_width / 2;
    center_y = data->window_height / 2;

	dx = x - center_x;
    sensitivity = 0.001; // Lower sensitivity for slower rotation

    if (dx != 0)
	{
        rotate_player(data, dx * sensitivity);
		// set flag to ignore the next event caused by warping
		ignore_next_warp = 1;
		// Warp the mouse pointer back to the center for continuous relative movement.
    	mlx_mouse_move(data->mlx, data->mlx_win, center_x, center_y);
	}

    return (0);
}

