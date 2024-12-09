/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:26:00 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/11/26 11:32:22 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (size != 0 && (count > ((size_t)-1) / size))
		return (NULL);
	result = (void *)malloc(size * count);
	if (!result)
		return (NULL);
	if (result)
		ft_bzero(result, size * count);
	return (result);
}
