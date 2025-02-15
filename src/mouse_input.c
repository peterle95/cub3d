/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:31:22 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 14:17:29 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// sets ignore_warp flag i.e.
// if the last event was caused by warping, ignore this event
// otherwise infinite loop of warp, call, warp, call, ...
// (faster processors might freeze up as they can take on a 
// larger number of calls. Or if there is simply no system
// filtering, the issue is exposed)
int	mouse_move(int x, int y, t_data *data)
{
	static int	ignore_warp = 0;
	int			center_x;
	int			center_y;
	int			dx;
	double		sensitivity;

	(void)y;
	if (ignore_warp)
	{
		ignore_warp = 0;
		return (0);
	}
	center_x = data->window_width / 2;
	center_y = data->window_height / 2;
	dx = x - center_x;
	sensitivity = 0.0001;
	if (dx <= -10 || dx >= 10)
	{
		rotate_player(data, dx * sensitivity);
		ignore_warp = 1;
		mlx_mouse_move(data->mlx, data->mlx_win, center_x, center_y);
	}
	return (0);
}
