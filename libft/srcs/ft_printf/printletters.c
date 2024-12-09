/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printletters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:08:57 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/11/26 13:35:36 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

int	print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	print_string(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		print_char(str[i]);
		i++;
	}
	return (i);
}

int	print_percent(char c)
{
	return (print_char(c));
}
