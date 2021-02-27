/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:51:39 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/26 11:36:20 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc((size + 1) * sizeof(*str));
	if (str == 0)
		return (0);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

static	void	ft_strdel(char **s)
{
	if (s == 0)
		return ;
	if (*s)
		free(*s);
	*s = 0;
}

static	int		ft_create_line(char **str, char **line)
{
	int		len;
	char	*aux;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != '\0')
		len++;
	if ((*str)[len] == '\n')
	{
		*line = ft_substr(*str, 0, len);
		aux = ft_strdup(&((*str)[len + 1]));
		free(*str);
		*str = aux;
		if ((*str)[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
		return (0);
	}
	return (1);
}

static	int		ft_return(char **str, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && str[fd] == NULL)
	{
		*line = ft_strnew(0);
		return (0);
	}
	return (ft_create_line(&str[fd], line));
}

int				get_next_line(int fd, char **line)
{
	static	char	*str[1];
	char			buf[BUFFER_SIZE + 1];
	char			*aux;
	int				ret;

	if (fd < 0 || line == 0 || BUFFER_SIZE == 0)
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buf);
		else
		{
			aux = ft_strjoin(str[fd], buf);
			free(str[fd]);
			str[fd] = aux;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	return (ft_return(str, line, ret, fd));
}
