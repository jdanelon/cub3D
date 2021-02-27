/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:52:37 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/29 11:30:53 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned	int	i;
	char			*last;

	i = 0;
	last = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			last = (char *)&s[i];
		i++;
	}
	if (last != 0)
		return (last);
	if (c == '\0')
		return ((char *)&s[i]);
	return (0);
}
