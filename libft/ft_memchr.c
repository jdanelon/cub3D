/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:39:19 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/28 16:42:54 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned	char	*aux_s;
	unsigned	int		i;

	i = 0;
	aux_s = (unsigned char *)s;
	while (i < n)
	{
		if (aux_s[i] == (unsigned char)c)
			return ((void *)&aux_s[i]);
		i++;
	}
	return (0);
}
