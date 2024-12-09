/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:10:06 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/11/26 11:32:59 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*temp;

	i = 0;
	temp = (const char *)s;
	while (i < n)
	{
		if (temp[i] == (char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
