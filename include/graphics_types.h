#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

typedef struct	s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
    int	dx;
    int	dy;
    int	sx;
    int	sy;
    int	err;
	int	e2;
}	t_line;

#endif
