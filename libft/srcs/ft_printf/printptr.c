/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:30:23 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/11/26 13:40:22 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static char	*unsignedlong_to_char(unsigned long adr)
{
	char			*hex_base;
	char			*result;
	int				len;
	unsigned long	tmp;

	hex_base = "0123456789abcdef";
	tmp = adr;
	len = 1;
	while (tmp > 15)
	{
		tmp /= 16;
		len++;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = 0;
	while (len--)
	{
		result[len] = hex_base[adr % 16];
		adr /= 16;
	}
	return (result);
}

int	print_hex(void *ptr)
{
	unsigned long	adress;
	char			*result;
	int				len;

	adress = (unsigned long)ptr;
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	result = unsignedlong_to_char(adress);
	if (!result)
		return (0);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(result, 1);
	len = ft_strlen(result) + 2;
	free(result);
	return (len);
}
