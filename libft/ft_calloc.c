/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:33:45 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/31 14:04:53 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*arr;
	unsigned	int	i;
	unsigned	int	total;

	i = 0;
	total = count * size;
	arr = malloc(total);
	if (arr == 0)
		return (0);
	while (i < total)
	{
		arr[i] = 0;
		i++;
	}
	return ((void *)arr);
}
