#include "cube3d.h"

t_line	*init_line(int x1, int y1, int x2, int y2)
{
	t_line *line;
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

// function to compute points along a line between (x1, y1) and (x2, y2)
// use of abs() and functions from math.h?
void compute_line_points(t_data *data, t_line *line)
{ 
	line->dx = abs(line->x2 - line->x1);
	line->dy = abs(line->y2 - line->y1);
	// step in x direction
	line->sx = (line->x1 < line->x2) ? 1 : -1;
	// Step in y direction
	line->sy = (line->y1 < line->y2) ? 1 : -1; 
	line->err = line->dx - line->dy;

	while (1) 
	{
		add_pixels(data, line->x1, line->y1);
		if (line->x1 == line->x2 && line->y1 == line->y2)
			break; 
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
	}
}
