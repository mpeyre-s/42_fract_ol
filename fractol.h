/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:50:35 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/15 17:59:57 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <math.h>

typedef struct s_pixel
{
	double	x_graph;
	double	y_graph;
}				t_pixel;

typedef struct s_fractol
{
	char			type;
	double			c1;
	double			c2;
	unsigned int	color;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	double			min_real;
	double			max_real;
	double			min_img;
	double			max_img;
	int				max_iter;
	t_pixel			fractal_params;
	int				color_scheme;
}						t_fractol;

// fractol.c
void			wiki(void);
void			handle_args(int argc, char *argv[]);
void			init(char type, double c1, double c2, unsigned int color);
t_fractol		init_tfractol(char type, double c1, double c2, unsigned int color);

// render.c
void			adjust_img_range(t_fractol *fractol, double real_range,
					double aspect_ratio);
void			adjust_real_range(t_fractol *fractol, double img_range,
					double aspect_ratio);
void			adjust_aspect_ratio(t_fractol *fractol);
unsigned int	iterate_pixel(int x, int y, t_fractol *fractol);
void			print_canvas(t_fractol *fractol);

// hooks.c
int				key_hook(int keycode, t_fractol *fractol);
int				mouse_hook(int button, int x, int y, t_fractol *fractol);
int				close_hook(t_fractol *fractol);
void			exit_fractol(t_fractol *fractol);

// mandelbrot.c
unsigned int	mandelbrot(int x, int y, t_fractol *fractol);
unsigned int	get_color(int i, t_fractol *fractol);

// julia.c
//unsigned int	julia(int x, int y, t_fractol *fractol);

#endif
