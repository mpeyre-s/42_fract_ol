/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:22:35 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/15 22:22:25 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	adjust_img_range(t_fractol *fractol, double real_range,
			double aspect_ratio)
{
	double	adjusted_img_range;
	double	img_center;

	adjusted_img_range = real_range / aspect_ratio;
	img_center = (fractol->max_img + fractol->min_img) / 2.0;
	fractol->min_img = img_center - adjusted_img_range / 2.0;
	fractol->max_img = img_center + adjusted_img_range / 2.0;
}

void	adjust_real_range(t_fractol *fractol, double img_range,
			double aspect_ratio)
{
	double	adjusted_real_range;
	double	real_center;

	adjusted_real_range = img_range * aspect_ratio;
	real_center = (fractol->max_real + fractol->min_real) / 2.0;
	fractol->min_real = real_center - adjusted_real_range / 2.0;
	fractol->max_real = real_center + adjusted_real_range / 2.0;
}

void	adjust_aspect_ratio(t_fractol *fractol)
{
	double	aspect_ratio;
	double	real_range;
	double	img_range;

	aspect_ratio = (double)fractol->width / fractol->height;
	real_range = fractol->max_real - fractol->min_real;
	img_range = fractol->max_img - fractol->min_img;
	if (real_range / img_range > aspect_ratio)
		adjust_img_range(fractol, real_range, aspect_ratio);
	else
		adjust_real_range(fractol, img_range, aspect_ratio);
}

void	print_canvas(t_fractol *fractol)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < fractol->height)
	{
		x = 0;
		while (x < fractol->width)
		{
			dst = fractol->addr + (y * fractol->line_length + x
					* (fractol->bits_per_pixel / 8));
			if (fractol->type == 'm')
				*(unsigned int *)dst = mandelbrot(x, y, fractol);
			// else if (fractol->type == 'j')
			// 	*(unsigned int *)dst = julia(x, y, fractol);
			else
				*(unsigned int *)dst = 0x000000;
			x++;
		}
		y++;
	}
}

unsigned int	get_color(int i, t_fractol *fractol)
{
	unsigned int	color;
	unsigned int	rgb[3];

	if (i == fractol->max_iter)
		return (0x000000);
	if (!fractol->color)
		return ((i * 1 % 256) << 16 | (i * 3 % 256) << 8 | (i * 5 % 256));
	color = fractol->color;
	rgb[0] = ((color >> 16) & 0xFF) * i / fractol->max_iter;
	rgb[1] = ((color >> 8) & 0xFF) * i / fractol->max_iter;
	rgb[2] = (color & 0xFF) * i / fractol->max_iter;
	return ((rgb[0] & 0xFF) << 16 | (rgb[1] & 0xFF) << 8 | (rgb[2] & 0xFF));
}
