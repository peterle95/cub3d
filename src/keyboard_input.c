/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:33 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/10 11:37:40 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>

int	key_up(int keycode, t_data *data)
{
	if (65307 == keycode)
		terminator(data);
	return (0);
}

int	key_down(int keycode, t_data *data)
{
	if (keycode == 'w' || keycode == 'W')
	{
		printf("forward\n");
		player_move(data, UP);
	}
	if (keycode == 's' || keycode == 'S')
	{
		printf("backward\n");
		player_move(data, DOWN);
	}
	if (keycode == 'a' || keycode == 'A')
	{
		printf("strafe left\n");
		move_player_strafe(data, -1);
	}
	if (keycode == 'd' || keycode == 'D')
	{
		printf("strafe right\n");
		move_player_strafe(data, 1);
	}
	return (0);
}
