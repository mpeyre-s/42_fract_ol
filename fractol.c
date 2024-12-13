/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:34:45 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/13 19:13:18 by mathispeyre      ###   ########.fr       */
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

void	init(char c)
{
	t_fractol	fractol;

	fractol.type = c;
	fractol.width = 1280;
	fractol.height = 720;
	fractol.min_real = -2.0;
	fractol.max_real = 1.0;
	fractol.min_img = -1.5;
	fractol.max_img = 1.5;
	fractol.max_iter = 256;
	fractol.mlx = mlx_init();
	fractol.win = mlx_new_window(fractol.mlx, fractol.width, fractol.height,
			"FRACTAL");
	fractol.img = mlx_new_image(fractol.mlx, fractol.width, fractol.height);
	fractol.addr = mlx_get_data_addr(fractol.img, &fractol.bits_per_pixel,
			&fractol.line_length, &fractol.endian);
	adjust_aspect_ratio(&fractol);
	print_canvas(&fractol);
	mlx_put_image_to_window(fractol.mlx, fractol.win, fractol.img, 0, 0);
	mlx_hook(fractol.win, 2, 1L << 0, key_hook, &fractol);
	mlx_hook(fractol.win, 17, 1L << 17, close_hook, &fractol);
	mlx_mouse_hook(fractol.win, mouse_hook, &fractol);
	mlx_loop(fractol.mlx);
}

void	handle_args(char c)
{
	if (c == 'M' || c == 'm' || c == '1')
		init('m');
	else if (c == 'J' || c == 'j' || c == '2')
		init('j');
	else
		wiki();
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (wiki(), 0);
	handle_args(argv[1][0]);
	return (0);
}
