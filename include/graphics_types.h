/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:55:44 by pmolzer           #+#    #+#             */
/*   Updated: 2025/02/07 12:55:45 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

# define N_TEXTURES 4

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

typedef struct	s_texture
{
	void	*ptr;
	char	*id;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct	s_textures
{
	t_texture	img[N_TEXTURES];
}	t_textures;


#endif


// printf("texture ptr:       %p\n", t->ptr);
// printf("texture id:        %s\n", t->id);
// printf("texture width:     %d\n", t->width);
// printf("texture height:    %d\n", t->height);
// printf("texture addr:      %p\n", t->addr);
// printf("texture bpp:       %d\n", t->bpp);
// printf("texture size_line: %d\n", t->size_line);
// printf("texture endian:    %d\n", t->endian);
