/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:17:03 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/30 17:47:05 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_len;
	char	*trim;
	int		abs_value;

	i = 0;
	if (s1 == 0 || set == 0)
		return (0);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	s1_len = ft_strlen(s1);
	while (s1_len != 0 && ft_strchr(set, s1[s1_len]))
		s1_len--;
	if (s1_len < i)
		abs_value = i - s1_len;
	else
		abs_value = s1_len - i;
	trim = ft_substr((char *)s1, i, abs_value + 1);
	return (trim);
}
