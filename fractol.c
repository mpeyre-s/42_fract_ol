/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:34:45 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/10 21:06:54 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	wiki(void)
{
	ft_printf("\n========== WIKI FRACT-OL ==========\n\n");
	ft_printf("At runtime, you must specify a fractal to display. ");
	ft_printf("Additional optional parameters can also be provided :\n\n");
	ft_printf("./fract-ol <type> <options>\n\n");
	ft_printf(" - M, m, or 1 : Mandelbrot fractal\n");
	ft_printf(" - J, j, or 2 : Julia fractal\n\n");
	ft_printf("For the Julia fractal set (and only for this set), ");
	ft_printf("two additional parameters can be provided as calculation ");
	ft_printf("values. These parameters correspond to a complex number that ");
	ft_printf("modifies the shape of the Julia fractal. They must be ");
	ft_printf("fractional numbers ranging from -2.0 to 2.0. Example :\n\n");
	ft_printf("./fractol J 0.285 -0.01\n\n");
	ft_printf("You can also specify a hexadecimal color to customize the ");
	ft_printf("fractal's appearance :\n\n");
	ft_printf("./fractol M 00CCFF\n\n");
	ft_printf("However, for the Julia set, the color option can only be ");
	ft_printf("used after specifying the calculation values :\n\n");
	ft_printf("./fractol J -0.4 0.6 65CD87\n\n");
	ft_printf("========== FRACT-OL CONTROLS ==========\n\n");
	ft_printf("|------------------------|--------------------|\n");
	ft_printf("|      scroll wheel      |  Zoom in and out   |\n");
	ft_printf("|------------------------|--------------------|\n");
	ft_printf("| echap or close control |   Quit fract-ol    |\n");
	ft_printf("|------------------------|--------------------|\n\n");
	ft_printf("Exiting properly...");
}
void	exit_fractol(void *mlx, void *win, t_data *img)
{
	if (img && img->img)
		mlx_destroy_image(mlx, img->img);
	if (win)
		mlx_destroy_window(mlx, win);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, void *param)
{
	t_data *img = ((t_data **)param)[0];
	void *mlx = ((void **)param)[1];
	void *win = ((void **)param)[2];

	if (keycode == 53)
		exit_fractol(mlx, win, img);
	return (0);
}

void adjust_aspect_ratio(t_graph *graph)
{
	double aspect_ratio = (double)graph->width / graph->height;
	double real_range = graph->max_real - graph->min_real;
	double img_range = graph->max_img - graph->min_img;

	if (real_range / img_range > aspect_ratio)
	{
		double adjusted_img_range = real_range / aspect_ratio;
		double img_center = (graph->max_img + graph->min_img) / 2.0;
		graph->min_img = img_center - adjusted_img_range / 2.0;
		graph->max_img = img_center + adjusted_img_range / 2.0;
	}
	else
	{
		double adjusted_real_range = img_range * aspect_ratio;
		double real_center = (graph->max_real + graph->min_real) / 2.0;
		graph->min_real = real_center - adjusted_real_range / 2.0;
		graph->max_real = real_center + adjusted_real_range / 2.0;
	}
}

int mouse_hook(int button, int x, int y, void *param)
{
	t_data *img = ((t_data **)param)[0];
	void *mlx = ((void **)param)[1];
	void *win = ((void **)param)[2];
	t_graph *graph = ((t_graph **)param)[3];

	double new_x = graph->min_real + ((double)x / graph->width) * (graph->max_real - graph->min_real);
	double new_y = graph->min_img + ((double)y / graph->height) * (graph->max_img - graph->min_img);

	double zoom_factor = (button == 4) ? 1.5 : (button == 5) ? (1 / 1.5) : 1.0;
	if (zoom_factor == 1.0)
		return (0);

	double new_real_range = (graph->max_real - graph->min_real) / zoom_factor;
	double new_img_range = (graph->max_img - graph->min_img) / zoom_factor;

	graph->min_real = new_x - ((double)x / graph->width) * new_real_range;
	graph->max_real = graph->min_real + new_real_range;

	graph->min_img = new_y - ((double)y / graph->height) * new_img_range;
	graph->max_img = graph->min_img + new_img_range;

	adjust_aspect_ratio(graph);

	print_canevas(img, graph);
	mlx_put_image_to_window(mlx, win, img->img, 0, 0);

	return (0);
}


int	close_hook(void *param)
{
	t_data *img = ((t_data **)param)[0];
	void *mlx = ((void **)param)[1];
	void *win = ((void **)param)[2];

	exit_fractol(mlx, win, img);
	return (0);
}

unsigned int	init_iterate_pixel(int x, int y, t_graph graph)
{
	t_pixel		pixel;
	double		zr;
	double		temp_zr;
	double		zi;

	int			i;

	pixel.x_graph = graph.min_real + ((double)x / graph.width)*(graph.max_real - graph.min_real);
	pixel.y_graph = graph.min_img + ((double)y / graph.height)*(graph.max_img - graph.min_img);

	zr = 0;
	zi = 0;
	i = 0;

	while (zr * zr + zi * zi < (double)4.0 && i < 256)
	{
		temp_zr = zr* zr - zi * zi + pixel.x_graph;
		zi = 2 * zr * zi + pixel.y_graph;
		zr = temp_zr;
		i++;
	}

	if (i == 256)
		return (0x000000);

	unsigned int red = (i * 1) % 256;
	unsigned int green = (i * 3) % 256;
	unsigned int blue = (i * 5) % 256;
	return (red << 16 | green << 8 | blue);
}

void	mandelbrot(void)
{
	int		width = 1280;
	int		height = 720;
	void	*mlx;
	void	*win;
	t_data	img;
	t_graph	graph;

	void	*params[4];

	graph.min_real = -2.0;
	graph.max_real = 1.0;
	graph.min_img = -1.5;
	graph.max_img = 1.5;
	graph.width = width;
	graph.height = height;
	adjust_aspect_ratio(&graph);

	mlx = mlx_init();
	win = mlx_new_window(mlx, width, height, "FRACTAL");

	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	print_canevas(&img, &graph);

	mlx_put_image_to_window(mlx, win, img.img, 0, 0);

	params[0] = &img;
	params[1] = mlx;
	params[2] = win;
	params[3] = &graph;

	mlx_hook(win, 2, 1L << 0, key_hook, params);
	mlx_hook(win, 17, 1L << 17, close_hook, params);
	mlx_mouse_hook(win, mouse_hook, params);

	mlx_loop(mlx);
}

void	print_canevas(t_data *img, t_graph *graph)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < graph->height)
	{
		x = 0;
		while (x < graph->width)
		{
			dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
			*(unsigned int *)dst = init_iterate_pixel(x, y, *graph);
			x++;
		}
		y++;
	}
}
void	handle_args(char c)
{
	if (c == 'M' || c == 'm' || c == '1')
		mandelbrot();
	else if (c == 'J' || c == 'j' || c == '2')
		mandelbrot();
	else
		wiki();
}

int main (int argc, char *argv[])
{
	if (argc < 2)
		return(wiki(), 0);
	handle_args(argv[1][0]);
	return (0);
}
