/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:37:59 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/28 19:48:40 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned	char	*aux_src;
	unsigned	char	*aux_dst;
	unsigned	int		i;

	i = 0;
	aux_src = (unsigned char *)src;
	aux_dst = (unsigned char *)dst;
	while (i < n)
	{
		aux_dst[i] = aux_src[i];
		if (aux_src[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
