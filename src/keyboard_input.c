/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:33 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 12:56:34 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>

int	key_up(int keycode, t_data *data)
{
	if (65307 == keycode)
		terminator(data, 0);
	return (0);
}

int	key_down(int keycode, t_data *data)
{
	// Use WASD for movement.
	if (keycode == 'w' || keycode == 'W') // Move forward
		player_move(data, UP);
	else if (keycode == 's' || keycode == 'S') // Move backward
		player_move(data, DOWN);
	else if (keycode == 'a' || keycode == 'A') // Strafe left
		player_move(data, LEFT);
	else if (keycode == 'd' || keycode == 'D') // Strafe right
		player_move(data, RIGHT);
	return (0);
}
