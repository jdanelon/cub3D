/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:46:01 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/29 14:34:02 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned	int	i;
	unsigned	int	n;
	unsigned	int	length;

	i = 0;
	n = 0;
	length = 0;
	while (src[length] != '\0')
		length++;
	while (dst[n] != '\0' && n < dstsize)
		n++;
	length += n;
	if (dstsize == 0 || dst[n] != '\0')
		return (length);
	while (src[i] != '\0' && (n + i) < (dstsize - 1))
	{
		dst[n + i] = src[i];
		i++;
	}
	dst[n + i] = '\0';
	return (length);
}
