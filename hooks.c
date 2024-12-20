/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:19:54 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/20 11:42:30 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == 53)
		exit_fractol(fractol);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	double	zoom_factor;
	double	range_x;
	double	range_y;

	if (button != 4 && button != 5)
		return (0);
	if (button == 4)
		zoom_factor = 1.5;
	else
		zoom_factor = 1 / 1.5;
	range_x = fractol->max_real - fractol->min_real;
	range_y = fractol->max_img - fractol->min_img;
	fractol->min_real += ((double)x / fractol->width) * range_x
		- (range_x / zoom_factor) * ((double)x / fractol->width);
	fractol->max_real = fractol->min_real + range_x / zoom_factor;
	fractol->min_img += ((double)y / fractol->height) * range_y
		- (range_y / zoom_factor) * ((double)y / fractol->height);
	fractol->max_img = fractol->min_img + range_y / zoom_factor;
	adjust_aspect_ratio(fractol);
	print_canvas(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
	return (0);
}

int	close_hook(t_fractol *fractol)
{
	exit_fractol(fractol);
	return (0);
}

int	exit_fractol(t_fractol *fractol)
{
	if (!fractol)
		return (0);
	if (fractol->img)
		mlx_destroy_image(fractol->mlx, fractol->img);
	if (fractol->win)
		mlx_destroy_image(fractol->mlx, fractol->win);
	if (fractol->mlx)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
	}
	exit(EXIT_SUCCESS);
}
