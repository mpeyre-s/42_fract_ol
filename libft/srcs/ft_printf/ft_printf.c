/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:37:58 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/11/26 12:30:57 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static int	printhub(char type, va_list parameters)
{
	if (type == 'c')
		return (print_char(va_arg(parameters, int)));
	else if (type == 's')
		return (print_string(va_arg(parameters, char *)));
	else if (type == 'p')
		return (print_hex(va_arg(parameters, void *)));
	else if (type == 'd' || type == 'i')
		return (print_base10(va_arg(parameters, int)));
	else if (type == 'u')
		return (print_unsigned10(va_arg(parameters, unsigned int)));
	else if (type == 'x' || type == 'X')
		return (hexhub(va_arg(parameters, unsigned int), type));
	else if (type == '%')
		return (print_percent('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	parameters;
	size_t	i;
	int		result;

	va_start(parameters, str);
	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			result += printhub(str[i + 1], parameters);
			i += 2;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			result++;
			i++;
		}
	}
	va_end(parameters);
	return (result);
}
