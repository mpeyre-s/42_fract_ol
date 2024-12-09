/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:24:26 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/12/04 16:29:30 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	ft_to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

static int	ft_get_digit(char c, int base)
{
	if (base <= 10)
	{
		if (c >= '0' && c < '0' + base)
			return (c - '0');
	}
	else
	{
		if (c >= '0' && c <= '9')
			return (c - '0');
		if (c >= 'a' && c < 'a' + (base - 10))
			return (10 + c - 'a');
	}
	return (-1);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;
	int	digit;

	if (!str || base < 2 || base > 16)
		return (0);
	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		digit = ft_get_digit(ft_to_lower(*str), base);
		if (digit == -1)
			break ;
		result = result * base + digit;
		str++;
	}
	return (result * sign);
}
