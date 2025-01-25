#include "window.h"

void	init_colour_fade(t_data *data)
{
	data->t = 0;
	data->r = 255;
	data->g = 0;
	data->b = 0;
}

int	terminator(t_data *data)
{
	printf("Hasta la vista, baby!\n");
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_data(data);
	exit(0);
}

int	key_up(int keycode, t_data *data)
{
	if (65307 == keycode)
		terminator(data);
	return (0);
}

// data not currently freed
void	init_img(t_data *data)
{
	data->img_data0 = malloc(sizeof(t_img_data));
	data->img_data0->img = mlx_new_image(data->mlx, 1920, 1080);
	data->img_data0->addr = mlx_get_data_addr(data->img_data0->img, &data->img_data0->bits_per_pixel,
			&data->img_data0->line_length, &data->img_data0->endian);

	data->img_data1 = malloc(sizeof(t_img_data));
	data->img_data1->img = mlx_new_image(data->mlx, 1920, 1080);
	data->img_data1->addr = mlx_get_data_addr(data->img_data1->img, &data->img_data1->bits_per_pixel,
			&data->img_data1->line_length, &data->img_data1->endian);

	if (DEBUG)
	{
		printf("bpp: %d, ll: %d, e: %d\n", data->img_data0->bits_per_pixel,
				data->img_data0->line_length, data->img_data0->endian);
		printf("addr: %p\n", data->img_data0->addr);
	}
}

void	put_pixel_to_img(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_data0->addr + (y * data->img_data0->line_length + x
			* (data->img_data0->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	set_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

void	free_2d_char_arr(char **arr)
{
	int	i;
	
	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


