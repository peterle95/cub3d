#ifndef WINDOW_H
#define WINDOW_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <X11/Xlib.h>
# include <X11/cursorfont.h>
# include <time.h>
# include <fcntl.h>
# include <stdbool.h>
# include "mlx.h"
# include "libft.h"
# include "graphics_types.h"

# define VALID_MAP_CHARS "01NESW "
# define VALID_PLAYER_CHARS "NSEW"
# define N_CONFIGS 7

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

typedef struct	s_player
{
	double	x;
	double	y;
	double	speed;
	double	rotation_speed;
	double	dir_x;    // Direction vector
	double	dir_y;
	double	plane_x;  // Camera plane
	double	plane_y;
	double	angle;
}	t_player;

typedef struct	s_ray
{
	double	pos_x;
	double	pos_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct	s_line_params
{
	int		x;
	int		draw_start;
	int		draw_end;
    t_ray	*ray;
}	t_line_params;

typedef struct	s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img_data	*img_data0;
	t_img_data	*img_data1;
	int			window_width;
	int			window_height;
	t_textures	textures;
	t_player	player;
	int			scalar;
	int			offset;
	t_ray		*ray;
	int			t;
	int			r;
	int			g;
	int			b;
	t_map		map;
	int			debug_mode;
}	t_data;

typedef enum s_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_dir;

typedef enum s_id
{
	BLACK
}	t_id;

// debug
void 	print_string_array(char **array, int n);

// functions in main temporarily
int	player_move(t_data *data, int dir);

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
int		load_map_data(t_data *data, char *f_name);
int		validate_map(t_data *data);
//	static int		init_ids(t_data *data);
//	static int	parse_line(t_data *data, char *line)

// load_map_utils
int		free_map_data(t_data *data);
bool	member_of_set(char c, char *set);
int		free_temp_return(char **temp, int r);
int		array_len(char **arr);
// static int		parse_map(t_data *data, char *line);

// graphics_image
void	init_img(t_data *data);
void	put_pixel_to_img(t_data *data, int x, int y, int color);
void	add_pixels(t_data *data, int x, int y);
void	add_random_pixels(t_data *data, int width, int height, int num_pixels);// test function
void	clear_image_to_colour(t_data *data, int colour);

// graphics_lines
t_line	*init_line(int x1, int y1, int x2, int y2);
void	compute_line_points(t_data *data, t_line *line);

// graphics_grid
int		draw_grid(t_data *data);
// static void	fill_square(t_data *data, int x, int y, int len_side)

// keyboard_input
int		key_down(int keycode, t_data *data);

// player_movement
int		player_move(t_data *data, int dir);

// player_position
void	init_player_position(t_data *data);

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

// dda
int      check_bounds(t_data *data, t_ray *ray);
void     init_ray(t_ray *ray, t_data *data, int x);
void     draw_floor_ceiling(t_data *data);
double   calculate_wall_x(t_ray *ray);
void     calculate_step_and_side_dist(t_ray *ray);
void     perform_dda(t_data *data, t_ray *ray);
void     calculate_perpendicular_distance(t_ray *ray);
void     check_wall_collision(t_data *data, t_ray *ray);

// raycasting
void	perform_dda(t_data *data, t_ray *ray);
void	draw_textured_line(t_data *data, t_line_params *line);
void	render_frame(t_data *data);
void	init_player_position(t_data *data);

// raycasting_visualisation
int		draw_raycast(t_data *data);

// draw
void	draw_floor_ceiling(t_data *data);
void	draw_floor(t_data *data, unsigned int floor_color);
void	draw_horizontal_line(t_data *data, int y, unsigned int color);
int		get_texture_number(t_ray *ray);
int		calculate_tex_x(t_ray *ray, t_texture *tex);
void	calculate_step_pos(t_data *data, t_line_params *line, t_texture *tex, double step_pos[2]);


#endif
