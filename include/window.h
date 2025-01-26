#ifndef WINDOW_H
#define WINDOW_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <X11/Xlib.h>
# include <time.h>
# include <fcntl.h>
# include <stdbool.h>
# include "mlx.h"
# include "libft.h"

# define VALID_MAP_CHARS "01NESW "
# define VALID_PLAYER_CHARS "NSEW"
# define N_CONFIGS 7
# define N_TEXTURES 4

# ifndef DEBUG
#  define DEBUG 0
# endif

// get_next_line buffer size
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

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
	char	**map_ids;
	char	***config;
	char	*flat_map;
	int		n_rows;
	char	**map_array;
    int     height;
    int     width;
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
	double pos_x; // Player position
	double pos_y;
	double dir_x; // Player direction vector
	double dir_y;
	double plane_x; // Camera plane
	double plane_y;
}	t_data;

typedef enum s_id
{
	BLACK
}	t_id;

// debug
void 	print_string_array(char **array, int n);

// error_msg
int		error(char *message);

// free_data
void	free_data(t_data *data);

// utils
void	init_colour_fade(t_data *data);
int		terminator(t_data *data);
int		key_up(int keycode, t_data *data);
void	init_img(t_data *data);
void	put_pixel_to_img(t_data *data, int x, int y, int color);
int		set_trgb(int t, int r, int g, int b);
void	add_random_pixels(t_data *data, int width, int height, int num_pixels);
void	clear_image_to_colour(t_data *data, int colour);
void	free_2d_char_arr(char **arr);

// load_map
//	static int		init_ids(t_data *data);
//	static int	parse_line(t_data *data, char *line)
int		load_map_data(t_data *data, char *f_name);
int		validate_map(t_data *data);

// load_map_utils
// static int		parse_map(t_data *data, char *line);
int		free_map_data(t_data *data);
bool	member_of_set(char c, char *set);
int		free_temp_return(char **temp, int r);
int		array_len(char **arr);

// get_next_line
char	*get_next_line(int fd);
char	*fetch(int fd, char **ln);
char	*freeb(char *buff);
int		gnl_strlen(char *str);
int		isin(char *str);
char	*set(char **ln, int fd);
char	*set_rem(char **ln, int fd);
char	*gnl_strjoin(char *buff, char **ln, int fd);
char	*set_line(char	**ln, int fd);
char	*freel(char **ln, int fd);

#endif
