/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:41:26 by jdanelon          #+#    #+#             */
/*   Updated: 2020/07/21 16:13:07 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned	char	*aux_src;
	unsigned	char	*aux_dst;
	unsigned	int		i;

	i = 0;
	aux_src = (unsigned char *)src;
	aux_dst = (unsigned char *)dst;
	if (aux_src == 0 && aux_dst == 0)
		return (0);
	while (i < n)
	{
		aux_dst[i] = aux_src[i];
		i++;
	}
	return (dst);
}
