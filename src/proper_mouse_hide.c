#include "cube3d.h"

int		doomed_mouse_hide(t_data *doomed_data, t_xvar *xvar, t_win_list *win)
{
	static char data[1] = {0};
	XColor dummy = {0};

	doomed_data->blank = XCreateBitmapFromData(xvar->display, win->window, data, 1, 1);
	doomed_data->cursor = XCreatePixmapCursor(xvar->display, doomed_data->blank,
			doomed_data->blank, &dummy, &dummy, 0, 0);
	XDefineCursor(xvar->display, win->window, doomed_data->cursor);
	return (0);
}

void	free_doomed_data(t_data *data, t_xvar *xvar)
{
	XFreePixmap(xvar->display, data->blank);
	data->blank = 0;
	XFreeCursor(xvar->display, data->cursor);
	data->cursor = 0;
}
