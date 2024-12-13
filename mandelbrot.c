/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:23:49 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/13 17:24:08 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(void)
{
	t_fractol	fractol;

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
