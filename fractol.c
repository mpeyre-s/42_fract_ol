/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:34:45 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/09 16:44:19 by mathispeyre      ###   ########.fr       */
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

int	close_hook(void *param)
{
	t_data *img = ((t_data **)param)[0];
	void *mlx = ((void **)param)[1];
	void *win = ((void **)param)[2];

	exit_fractol(mlx, win, img);
	return (0);
}
int	handle_args(char c)
{
	if (c == 'M' || c == 'm' || c == '1' || c == 'J' || c == 'j' || c == '2')
		return (1);
	return (0);
}

void	blue_wall(void)
{
	void	*mlx;
	void	*win;
	t_data	img;
	int		largeur = 800;
	int		hauteur = 600;
	void	*params[3];

	mlx = mlx_init();
	win = mlx_new_window(mlx, largeur, hauteur, "BLUE WALL");
	img.img = mlx_new_image(mlx, largeur, hauteur);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int y = 0; y < hauteur; y++)
	{
		for (int x = 0; x < largeur; x++)
		{
			char *dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
			*(unsigned int *)dst = 0x000000FF;
		}
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);

	params[0] = &img;
	params[1] = mlx;
	params[2] = win;

	mlx_hook(win, 2, 1L << 0, key_hook, params);
	mlx_hook(win, 17, 1L << 17, close_hook, params);

	mlx_loop(mlx);
}

int main (int argc, char *argv[])
{
	if (argc < 2 || !handle_args(argv[1][0]))
		return(wiki(), 0);
	if (argv[1][0] == 'M')
		blue_wall();
	return (0);
}
