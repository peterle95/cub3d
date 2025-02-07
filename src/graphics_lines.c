/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:27 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 15:07:03 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_line	*init_line(int x1, int y1, int x2, int y2)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	line->x1 = x1;
	line->y1 = y1;
	line->x2 = x2;
	line->y2 = y2;
	line->dx = 0;
	line->dy = 0;
	line->sx = 0;
	line->sy = 0;
	line->err = 0;
	line->e2 = 0;
	return (line);
}

static void	initialize_line(t_line *line)
{
	line->dx = abs(line->x2 - line->x1);
	line->dy = abs(line->y2 - line->y1);
	if (line->x1 < line->x2)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y1 < line->y2)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

static int	update_line_position(t_line *line)
{
	if (line->x1 == line->x2 && line->y1 == line->y2)
		return (0);
	line->e2 = 2 * line->err;
	if (line->e2 > -(line->dy))
	{
		line->err -= line->dy;
		line->x1 += line->sx;
	}
	if (line->e2 < line->dx)
	{
		line->err += line->dx;
		line->y1 += line->sy;
	}
	return (1);
}

// function to compute points along a line between (x1, y1) and (x2, y2)
void	compute_line_points(t_data *data, t_line *line)
{
	initialize_line(line);
	while (1)
	{
		add_pixels(data, line->x1, line->y1);
		if (!update_line_position(line))
			break ;
	}
}
