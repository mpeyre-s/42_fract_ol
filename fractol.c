/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:34:45 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/16 18:57:56 by mathispeyre      ###   ########.fr       */
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
	ft_printf("./fract-ol J 0.285 -0.01\n\n");
	ft_printf("You can also specify a hexadecimal color to customize the ");
	ft_printf("fractal's appearance :\n\n");
	ft_printf("./fract-ol M 00CCFF\n\n");
	ft_printf("However, for the Julia set, the color option can only be ");
	ft_printf("used after specifying the calculation values :\n\n");
	ft_printf("./fract-ol J -0.4 0.6 65CD87\n\n");
	ft_printf("========== FRACT-OL CONTROLS ==========\n\n");
	ft_printf("|------------------------|--------------------|\n");
	ft_printf("|      scroll wheel      |  Zoom in and out   |\n");
	ft_printf("|------------------------|--------------------|\n");
	ft_printf("| echap or close control |   Quit fract-ol    |\n");
	ft_printf("|------------------------|--------------------|\n\n");
	ft_printf("Exiting properly...");
}

t_fractol	init_tfractol(char type, double c1, double c2, unsigned int color)
{
	t_fractol	fractol;

	fractol.type = type;
	fractol.c1 = c1;
	fractol.c2 = c2;
	if (color)
		fractol.color = color;
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
	return (fractol);
}

void	init(char type, double c1, double c2, unsigned int color)
{
	t_fractol	fractol;

	fractol = init_tfractol(type, c1, c2, color);
	adjust_aspect_ratio(&fractol);
	print_canvas(&fractol);
	mlx_put_image_to_window(fractol.mlx, fractol.win, fractol.img, 0, 0);
	mlx_hook(fractol.win, 2, 1L << 0, key_hook, &fractol);
	mlx_hook(fractol.win, 17, 1L << 17, close_hook, &fractol);
	mlx_mouse_hook(fractol.win, mouse_hook, &fractol);
	mlx_loop(fractol.mlx);
}

void	handle_args(int argc, char *argv[])
{
	if (argv[1][0] == 'M' || argv[1][0] == 'm' || argv[1][0] == '1')
	{
		if (argc == 2)
			init('m', 0, 0, 0);
		else if (argc == 3 && ft_atouint(argv[2]))
			init('m', 0, 0, ft_atouint(argv[2]));
	}
	else if (argv[1][0] == 'J' || argv[1][0] == 'j' || argv[1][0] == '2')
	{
		if (argc == 2)
			init('j', -0.8, 0.156, 0);
		else if (argc == 4 && ft_atodouble(argv[2]) && ft_atodouble(argv[3]))
			init('j', ft_atodouble(argv[2]), ft_atodouble(argv[3]), 0);
		else if (argc == 5 && ft_atodouble(argv[2]) && ft_atodouble(argv[3]) && ft_atouint(argv[4]))
			init('j', ft_atodouble(argv[2]), ft_atodouble(argv[3]), ft_atouint(argv[4]));
	}
	wiki();
}

int	main(int argc, char *argv[])
{
	if (argc < 2 || argc > 5)
		return (wiki(), 0);
	handle_args(argc, argv);
	return (0);
}
