/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:48 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/09 11:26:20 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// this is probably doubling up terminator function
// Function to handle window close event
int	close_window(t_data *data)
{
	if (data->textures.img[0].ptr)
		mlx_destroy_image(data->mlx, data->textures.img[0].ptr);
	if (data->img_data0->img)
		mlx_destroy_image(data->mlx, data->img_data0->img);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}

int	mouse_mv(int mousecode, int x, int y, t_data *data)
{
	(void)data;
	printf("x: %d y: %d\n", x, y);
	if (mousecode == 1)
		printf("click\n");
	return (0);
}

int	load_texture(t_data *data, char *path, char *id, int index)
{
	if (!path) {
		printf("Error: Invalid texture path for %s\n", id);
		return (0);
	}

	data->textures.img[index].ptr = mlx_xpm_file_to_image(data->mlx, path,
			&data->textures.img[index].width,
			&data->textures.img[index].height);
			
	if (!data->textures.img[index].ptr) {
		printf("Error: Failed to load texture %s at path %s\n", id, path);
		return (0);
	}

	data->textures.img[index].id = id;
	data->textures.img[index].addr = mlx_get_data_addr(data->textures.img[index].ptr,
			&(data->textures.img[index].bpp),
			&(data->textures.img[index].size_line),
			&(data->textures.img[index].endian));
			
	if (!data->textures.img[index].addr) {
		printf("Error: Failed to get texture data address for %s\n", id);
		mlx_destroy_image(data->mlx, data->textures.img[index].ptr);
		return (0);
	}
	
	return (1);
}

// sky texture must be large enough (have default to colour if not big enough)
int	load_textures_from_config(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.config[i])
	{
		if (ft_strncmp(data->map.config[i][0], "WE", 3) == 0)
		{
			if (!load_texture(data, data->map.config[i][1], "wall_texture_west", 0))
				return (1);
		}
		else if (ft_strncmp(data->map.config[i][0], "EA", 3) == 0)
		{
			if (!load_texture(data, data->map.config[i][1], "wall_texture_east", 1))
				return (1);
		}
		else if (ft_strncmp(data->map.config[i][0], "NO", 3) == 0)
		{
			if (!load_texture(data, data->map.config[i][1], "wall_texture_north", 2))
				return (1);
		}
		else if (ft_strncmp(data->map.config[i][0], "SO", 3) == 0)
		{
			if (!load_texture(data, data->map.config[i][1], "wall_texture_south", 3))
				return (1);
		}
		i++;
	}
	return (0);
}
///////////////////////////////////////////////////
// structs and vars from minilibx redefined here //
// as not exposed by library                     //
///////////////////////////////////////////////////
# define MLX_MAX_EVENT LASTEvent

typedef struct	s_event_list
{
	int		mask;
	int		(*hook)();
	void	*param;
}				t_event_list;

typedef struct	s_win_list
{
	Window				window;
	GC					gc;
	struct s_win_list	*next;
	int					(*mouse_hook)();
	int					(*key_hook)();
	int					(*expose_hook)();
	void				*mouse_param;
	void				*key_param;
	void				*expose_param;
	t_event_list		hooks[MLX_MAX_EVENT];
}				t_win_list;

typedef struct	s_xvar
{
	Display		*display;
	Window		root;
	int			screen;
	int			depth;
	Visual		*visual;
	Colormap	cmap;
	int			private_cmap;
	t_win_list	*win_list;
	int			(*loop_hook)();
	void		*loop_param;
	int			use_xshm;
	int			pshm_format;
	int			do_flush;
	int			decrgb[6];
	Atom		wm_delete_window;
	Atom		wm_protocols;
	int 		end_loop;
}				t_xvar;
/////////////////////////////////////////////////
// end                                         //
/////////////////////////////////////////////////

void init_textures(t_data *data)
{
    for (int i = 0; i < MAX_TEXTURES; i++) {
        data->textures.img[i].ptr = NULL;
        data->textures.img[i].addr = NULL;
        data->textures.img[i].width = 0;
        data->textures.img[i].height = 0;
        data->textures.img[i].bpp = 0;
        data->textures.img[i].size_line = 0;
        data->textures.img[i].endian = 0;
        data->textures.img[i].id = NULL;
    }
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (0);
	init_data(&data);
	if (load_map_data(&data, argv[1]) != 0)
		return (error("Invalid map configuration"));
	if (validate_map(&data))
		return (error("Invalid map configuration"));
	init_colour_fade(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.window_width, data.window_height, "dooomed");
	init_img(&data);
	init_textures(&data);
	if (load_textures_from_config(&data)) {
		return (error("Failed to load textures"));
	}
	init_hooks(&data);

	// Grab the pointer to restrict it to the window
	XGrabPointer(
		((t_xvar *)data.mlx)->display,
		((t_win_list *)data.mlx_win)->window,
		False,  // Don't propagate events outside this window
		ButtonMotionMask | PointerMotionMask,  // Listen for pointer motion
		GrabModeAsync,  // Async mode for pointer grab
		GrabModeAsync,  // Async mode for pointer grab
		((t_win_list *)data.mlx_win)->window,  // Confine to the window
		None,  // No cursor change
		CurrentTime
	);

	XWarpPointer(((t_xvar *)data.mlx)->display, None, ((t_win_list *)data.mlx_win)->window,  0, 0, 0, 0, data.window_width / 2, data.window_height / 2);
	XFlush(((t_xvar *)data.mlx)->display);


	mlx_mouse_hide(data.mlx, data.mlx_win);
	init_player(&data);
	init_player_position(&data);
	mlx_loop(data.mlx);
}
