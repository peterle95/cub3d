/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:33 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	key_up(int keycode, t_data *data)
{
	if (65307 == keycode)
		terminator(data, 0);
	return (0);
}

int	key_down(int keycode, t_data *data)
{
	if (keycode == 'w' || keycode == 'W')
		player_move(data, UP);
	else if (keycode == 's' || keycode == 'S')
		player_move(data, DOWN);
	else if (keycode == 'a' || keycode == 'A')
		player_move(data, LEFT);
	else if (keycode == 'd' || keycode == 'D')
		player_move(data, RIGHT);
	return (0);
}
