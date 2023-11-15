/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:55:19 by anollero          #+#    #+#             */
/*   Updated: 2023/11/15 10:14:46 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"

size_t	ft_strlen(const char *cadena)
{
	int	index;

	index = 0;
	while (cadena[index] != '\0')
		index++;
	return (index);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	pointer;

	pointer = 0;
	while (pointer != n)
	{
		*((unsigned char *)s + pointer) = '\0';
		pointer++;
	}
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dupped;
	int		count;

	len = ft_strlen(s);
	count = 0;
	dupped = (char *)ft_calloc(len + 1, sizeof(char));
	if (dupped == 0)
		return (0);
	while (s[count] != '\0')
	{
		dupped[count] = s[count];
		count++;
	}
	dupped[count] = '\0';
	return (dupped);
}

int	ft_strnchr(char *str, char car)
{
	int	n;

	n = 0;
	while (*(str + n))
	{
		if (*(str + n) == car)
			return (1);
		n++;
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize == 1)
		dst[0] = 0;
	while (src[count] != '\0' && count < dstsize - 1)
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = 0;
	return (ft_strlen(src));
}
