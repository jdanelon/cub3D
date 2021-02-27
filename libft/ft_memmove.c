/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:42:24 by jdanelon          #+#    #+#             */
/*   Updated: 2020/07/21 16:13:24 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned	char	*aux_src;
	unsigned	char	*aux_dst;
	unsigned	int		i;

	i = 0;
	aux_src = (unsigned char *)src;
	aux_dst = (unsigned char *)dst;
	if (aux_src == 0 && aux_dst == 0)
		return (0);
	if (aux_src < aux_dst)
	{
		while (len-- != 0)
			aux_dst[len] = aux_src[len];
	}
	else
	{
		while (i < len)
		{
			aux_dst[i] = aux_src[i];
			i++;
		}
	}
	return (dst);
}
