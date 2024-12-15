/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:04:22 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/15 18:16:22 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static double	ft_pow(double base, int exp)
{
	double	result;

	result = 1.0;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	while (exp < 0)
	{
		result /= base;
		exp++;
	}
	return (result);
}

static size_t	parse_integer_part(const char *str, double *result)
{
	size_t	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*result = *result * 10.0 + (str[i] - '0');
		i++;
	}
	return (i);
}

static size_t	parse_fraction_part(const char *str, double *result)
{
	double	fraction;
	size_t	i;

	fraction = 0.0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fraction = fraction * 10.0 + (str[i] - '0');
		i++;
	}
	*result += fraction * ft_pow(10.0, -(int)i);
	return (i);
}

double	ft_atodouble(const char *str)
{
	double	result;
	int		sign;
	size_t	i;

	if (!str)
		return (0.0);
	result = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	i += parse_integer_part(&str[i], &result);
	if (str[i] == '.')
		i += parse_fraction_part(&str[i + 1], &result);
	return (result * sign);
}
