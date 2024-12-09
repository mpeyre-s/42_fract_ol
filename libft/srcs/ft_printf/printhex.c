/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:58:52 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/11/26 13:36:42 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

int	ft_hexlen(unsigned int nb)
{
	int	result;

	result = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		result++;
	}
	return (result);
}

void	ft_print_hexlower(unsigned int nb)
{
	char	c;
	char	*hex_base;

	hex_base = "0123456789abcdef";
	if (nb > 15)
		ft_print_hexlower(nb / 16);
	c = hex_base[nb % 16];
	ft_putchar_fd(c, 1);
}

void	ft_print_hexupper(unsigned int nb)
{
	char	c;
	char	*hex_base;

	hex_base = "0123456789ABCDEF";
	if (nb > 15)
		ft_print_hexupper(nb / 16);
	c = hex_base[nb % 16];
	ft_putchar_fd(c, 1);
}

int	hexhub(unsigned int nb, char type)
{
	if (type == 'x')
	{
		ft_print_hexlower(nb);
		return (ft_hexlen(nb));
	}
	else if (type == 'X')
	{
		ft_print_hexupper(nb);
		return (ft_hexlen(nb));
	}
	return (0);
}
