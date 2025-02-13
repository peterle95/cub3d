/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:04:29 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/13 15:26:03 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

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
# include "exposed_minilibx_guts.h"

# define VALID_MAP_CHARS "01NESW \n"
# define VALID_PLAYER_CHARS "NSEW"
# define N_CONFIGS 7
# define POINTER_MOTION 1L << 6
# define KEY_PRESS 1L << 0
# define KEY_RELEASE 1L << 1
# define MAX_TEXTURES 6

# ifndef DEBUG
#  define DEBUG 0
# endif

// get_next_line buffer size
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_img_data
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
	int		height;
	int		width;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		elements_found;
	int		id;
	int		n;
	unsigned int floor_color;
	unsigned int ceiling_color;
}	t_map;

typedef struct	s_player
{
	double	x;
	double	y;
	double	speed;
	double	rotation_speed;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
}	t_player;

typedef struct s_ray
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
	int			ceiling_loaded;
	int			debug_mode;
}	t_data;

typedef enum s_texture_index
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	CEILING,
}	t_texture_index;

typedef enum s_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_dir;

typedef enum s_id
{
	BLACK,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	SKY_BLUE,
	EARTH_BROWN,
}	t_id;

// debug
void	print_string_array(char **array, int n);

// functions in main temporarily
int		player_move(t_data *data, int dir);

// error_msg
int		error(char *message);

// free_data
void	free_data(t_data *data);
int		close_window(t_data *data);


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
//	 int		init_ids(t_data *data);
//	 int	parse_line(t_data *data, char *line)

// load_map_utils
int		free_map_data(t_data *data);
bool	member_of_set(char c, char *set);
int		free_temp_return(char **temp, int r);
int		array_len(char **arr);
int open_map_file(const char *f_name);
int process_single_line(t_data *data, char *line, int fd);
int process_map_lines(t_data *data, int fd);
void debug_print_map(t_data *data);
int	load_map_clean_up(t_data *data, char *line, int fd);
int parse_line(t_data *data, char *line);
void cleanup_on_error(t_data *data, int row);
int	flat_map_to_map_array(t_data *data);
int	load_map_clean_up(t_data *data, char *line, int fd);
int check_file_readable(const char *f_name);
int allocate_map_array(t_data *data);
int allocate_and_init_row(t_data *data, int row);
int	copy_chars(t_data *data, char *flat_map);
int process_config_line(t_data *data, char *line);
int	parse_map(t_data *data, char *line);
int	no_valid_id(t_data *data, char *line);


// graphics_image
void	init_img(t_data *data);
void	put_pixel_to_img(t_data *data, int x, int y, int color);
void	add_pixels(t_data *data, int x, int y);
void	add_random_pixels(t_data *data, int width, int height, int num_pixels);//test function
void	clear_image_to_colour(t_data *data, int colour);

// graphics_lines
t_line	*init_line(int x1, int y1, int x2, int y2);
void	compute_line_points(t_data *data, t_line *line);

// graphics_grid
int		draw_grid(t_data *data);
//  void	fill_square(t_data *data, int x, int y, int len_side)

// keyboard_input
int		key_down(int keycode, t_data *data);
void	move_player_strafe(t_data *data, double direction);

// mouse_input
int		mouse_move(int x, int y, t_data *data);
int		mouse_mv(int mousecode, int x, int y, t_data *data);

// player_movement
int		player_move(t_data *data, int dir);
void	rotate_player(t_data *data, double angle);

// draw
int		draw(t_data *data);
int		render_with_transparency(t_data *data, t_texture *t, int img_x, int img_y);
int		draw_player_position(t_data *data);
void 	draw_ceiling(t_data *data);

// initialization
int		init_data(t_data *data);
int		init_hooks(t_data *data);
int		init_player(t_data *data);

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

// raycasting
void	perform_dda(t_data *data, t_ray *ray);
void	draw_textured_line(t_data *data, t_line_params *line);
void	render_frame(t_data *data);
void	init_player_position(t_data *data);

// raycasting_visualisation
int		draw_raycast(t_data *data);

#endif
