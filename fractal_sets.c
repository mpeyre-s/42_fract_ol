/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:23:49 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/16 18:26:56 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	mandelbrot(int x, int y, t_fractol *fractol)
{
	t_pixel	pixel;
	double	zr;
	double	zi;
	double	temp_zr;
	int		i;

	pixel.x_graph = fractol->min_real + ((double)x / fractol->width)
		* (fractol->max_real - fractol->min_real);
	pixel.y_graph = fractol->min_img + ((double)y / fractol->height)
		* (fractol->max_img - fractol->min_img);
	zr = 0;
	zi = 0;
	i = 0;
	while (zr * zr + zi * zi < 4.0 && i < fractol->max_iter)
	{
		temp_zr = zr * zr - zi * zi + pixel.x_graph;
		zi = 2 * zr * zi + pixel.y_graph;
		zr = temp_zr;
		i++;
	}
	return (get_color(i, fractol));
}

unsigned int	julia(int x, int y, t_fractol *fractol)
{
	t_pixel	pixel;
	double	zr;
	double	zi;
	double	temp_zr;
	int		i;

	pixel.x_graph = fractol->min_real + ((double)x / fractol->width)
		* (fractol->max_real - fractol->min_real);
	pixel.y_graph = fractol->min_img + ((double)y / fractol->height)
		* (fractol->max_img - fractol->min_img);
	zr = pixel.x_graph;
	zi = pixel.y_graph;
	i = 0;
	while (zr * zr + zi * zi < 4.0 && i < fractol->max_iter)
	{
		temp_zr = zr * zr - zi * zi + fractol->c1;
		zi = 2 * zr * zi + fractol->c2;
		zr = temp_zr;
		i++;
	}
	return (get_color(i, fractol));
}
