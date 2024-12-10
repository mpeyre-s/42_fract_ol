/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:50:35 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/10 15:04:46 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_graph
{
	double	min_img;
	double	max_img;
	double	min_real;
	double	max_real;
	int		width;
	int		height;
}				t_graph;

typedef struct	s_pixel
{
	double	x_graph;
	double	y_graph;
}				t_pixel;

void	print_canevas(t_data *img, t_graph *graph);

#endif
