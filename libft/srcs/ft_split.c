/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:44:51 by mathispeyre       #+#    #+#             */
/*   Updated: 2024/11/26 11:33:28 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	sizewords(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	nbwords(char const *s, char c)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			result++;
		i++;
	}
	return (result);
}

static char	*makewords(char const *s, char c)
{
	size_t	i;
	size_t	size;
	char	*result;

	i = 0;
	size = sizewords(s, c);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result || !s)
		return (NULL);
	while (i < size)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

static void	freewords(char **result, size_t i)
{
	while (i--)
		free(result[i]);
	free(result);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**result;

	i = 0;
	result = malloc((nbwords(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			result[i] = makewords(s, c);
			if (!result[i])
			{
				freewords(result, i);
				return (NULL);
			}
			s += sizewords(s, c);
			i++;
		}
		else
			s++;
	}
	result[i] = 0;
	return (result);
}
