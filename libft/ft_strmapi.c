/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:45:27 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/30 17:20:59 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s_map;
	size_t			len;
	unsigned	int	i;

	i = 0;
	if (s == 0 || f == 0)
		return (0);
	len = ft_strlen(s);
	s_map = (char *)malloc(len + 1);
	if (s_map == 0)
		return (0);
	while (s[i] != '\0')
	{
		s_map[i] = f(i, s[i]);
		i++;
	}
	s_map[i] = '\0';
	return (s_map);
}
