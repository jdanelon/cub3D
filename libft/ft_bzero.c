/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:31:58 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/28 16:40:34 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned	char	*aux;
	unsigned	int		i;

	i = 0;
	aux = (unsigned char *)s;
	while (i < n)
	{
		aux[i] = '\0';
		i++;
	}
}
