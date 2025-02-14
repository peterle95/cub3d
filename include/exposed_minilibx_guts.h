/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exposed_minilibx_guts.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:30:38 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/14 10:32:23 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// structures from minilibx redefined here as not 
// exposed by library

// place in main after init_hooks():

	// XGrabPointer(
	// 	((t_xvar *)data.mlx)->display,
	// 	((t_win_list *)data.mlx_win)->window,
	// 	False,  // propagation of events outside window
	// 	ButtonMotionMask | PointerMotionMask,  // listen for pointer motion
	// 	GrabModeAsync,  // async mode for pointer grab
	// 	GrabModeAsync,  // async mode for pointer grab
	// 	((t_win_list *)data.mlx_win)->window,  // confine pointer to window
	// 	None,  // no cursor change
	// 	CurrentTime
	// );
	// XWarpPointer(((t_xvar *)data.mlx)->display, 
	// None, ((t_win_list *)
	// data.mlx_win)->window,  0, 0, 0, 0, 
	// data.window_width / 2, data.window_height / 2);
	// XFlush(((t_xvar *)data.mlx)->display);

#ifndef EXPOSED_MINILIBX_GUTS_H
# define EXPOSED_MINILIBX_GUTS_H

# include <X11/Xlib.h>

# define MLX_MAX_EVENT LASTEvent

typedef struct s_event_list
{
	int		mask;
	int		(*hook)();
	void	*param;
}				t_event_list;

typedef struct s_win_list
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

typedef struct s_xvar
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
	int			end_loop;
}				t_xvar;

#endif
