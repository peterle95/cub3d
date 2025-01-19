#ifndef WINDOW_H
#define WINDOW_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <X11/Xlib.h>
# include <time.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

typedef struct	s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	**map_ids;
	char	**map_array;
    int     map_height;
    int     map_width;
    int     player_x;
    int     player_y;
    char    player_dir;
    int     elements_found;
	int		id;
	int		n;
}	t_map;

typedef struct	s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img_data	*img_data0;
	t_img_data	*img_data1;
	int			t;
	int			r;
	int			g;
	int			b;
	t_map		map;
	int			debug_mode;
}	t_data;

typedef enum s_id
{
	BLACK
}	t_id;

void	init_colour_fade(t_data *data);
int		terminator(t_data *data);
int		key_up(int keycode, t_data *data);
void	init_img(t_data *data);
void	put_pixel_to_img(t_data *data, int x, int y, int color);
int		set_trgb(int t, int r, int g, int b);
void	add_random_pixels(t_data *data, int width, int height, int num_pixels);
void	clear_image_to_colour(t_data *data, int colour);
int		load_map_data(t_data *data, char *f_name);
int		validate_map(t_data *data);
int		error(char *message);
#endif
