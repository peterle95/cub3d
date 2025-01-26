#include "window.h"

void	init_img(t_data *data)
{
	data->img_data0 = malloc(sizeof(t_img_data));
	// error
	data->img_data0->img = mlx_new_image(data->mlx, 1920, 1080);
	data->img_data0->addr = mlx_get_data_addr(data->img_data0->img, &data->img_data0->bits_per_pixel,
			&data->img_data0->line_length, &data->img_data0->endian);

	// data->img_data1 = malloc(sizeof(t_img_data));
	// data->img_data1->img = mlx_new_image(data->mlx, 1920, 1080);
	// data->img_data1->addr = mlx_get_data_addr(data->img_data1->img, &data->img_data1->bits_per_pixel,
	// 		&data->img_data1->line_length, &data->img_data1->endian);

	if (DEBUG)
	{
		printf("bpp: %d, ll: %d, e: %d\n", data->img_data0->bits_per_pixel,
				data->img_data0->line_length, data->img_data0->endian);
		printf("addr: %p\n", data->img_data0->addr);
	}
}

// add width and height to data
void	put_pixel_to_img(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
		char	*dst;

		dst = data->img_data0->addr + (y * data->img_data0->line_length + x
				* (data->img_data0->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	add_pixels(t_data *data, int x, int y)
{
	unsigned int color = 0xFFFFFFFF;
	put_pixel_to_img(data, x, y, color);
}

void	add_random_pixels(t_data *data, int width, int height, int num_pixels)
{
    srand(time(NULL));
    for (int i = 0; i < num_pixels; i++) 
	{
        int x = rand() % width;
        int y = rand() % height;
        unsigned int color = (rand() % 0xFFFFFF) | 0xFF000000;
        put_pixel_to_img(data, x, y, color);
    }
}

// is this efficient? think about image buffering and limiting redraw
void	clear_image_to_colour(t_data *data, int colour)
{
	int	x;
	int	y;
	int	width = 1920;
	int	height = 1080;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			put_pixel_to_img(data, x, y, colour);
		}
	}
}

