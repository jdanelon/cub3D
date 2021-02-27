/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:32:56 by jdanelon          #+#    #+#             */
/*   Updated: 2020/01/31 11:19:11 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_words_count(char const *s, char c)
{
	int	i;
	int	w_count;

	i = 0;
	w_count = 0;
	while (s[i] != '\0')
	{
		if ((i > 0 && s[i - 1] == c && s[i] != c) || (i == 0 && s[i] != c))
			w_count++;
		i++;
	}
	return (w_count);
}

static	int		ft_words_size(char const *s, char c, int i)
{
	int	w_size;

	w_size = 0;
	while (s[i] != c && s[i] != '\0')
	{
		w_size++;
		i++;
	}
	return (w_size);
}

static	char	**ft_free(char const **word, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)word[j]);
	}
	free(word);
	return (0);
}

static	char	**ft_separate(char const *s, char **word, char c, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		k = 0;
		while (s[i] == c)
			i++;
		word[j] = (char *)malloc(ft_words_size(s, c, i) + 1);
		if (word[j] == 0)
			return (ft_free((char const **)word, j));
		while (s[i] != '\0' && s[i] != c)
			word[j][k++] = s[i++];
		word[j][k] = '\0';
		j++;
	}
	word[j] = 0;
	return (word);
}

char			**ft_split(char const *s, char c)
{
	int		len;
	char	**words;

	if (s == 0)
		return (0);
	len = ft_words_count(s, c);
	words = (char **)malloc((len + 1) * sizeof(char *));
	if (words == 0)
		return (0);
	return (ft_separate(s, words, c, len));
}
