/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:41:54 by jdanelon          #+#    #+#             */
/*   Updated: 2020/07/21 16:13:42 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_number_size(int n)
{
	int				size;
	unsigned	int	nbr;

	size = 0;
	if (n < 0)
	{
		nbr = -n;
		size++;
	}
	else
		nbr = n;
	while (nbr >= 10)
	{
		nbr /= 10;
		size++;
	}
	return (size + 1);
}

char		*ft_itoa(int n)
{
	unsigned	int	nbr;
	int				n_char;
	char			*str;

	n_char = ft_number_size(n);
	str = (char *)malloc(n_char + 1);
	if (str)
		return (0);
	str[n_char] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		nbr = -n;
	}
	else
		nbr = n;
	while (nbr >= 10)
	{
		str[n_char - 1] = (char)(nbr % 10 + '0');
		n_char--;
		nbr /= 10;
	}
	str[n_char - 1] = (char)(nbr % 10 + '0');
	return (str);
}
