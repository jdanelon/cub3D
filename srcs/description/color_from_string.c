/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_from_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:50:37 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 14:52:38 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	int		check_line_format(t_window *win_infos, int first_char_pos,
								char *str, int c)
{
	int	i;

	if (!str || str[first_char_pos] != c ||
			!ft_is_whitespace(str[first_char_pos + 1]))
		return (ERROR);
	i = first_char_pos + 1;
	while (ft_is_whitespace(str[i]))
		i++;
	while (ft_isdigit(str[i]) || (str[i] == ',' && str[i + 1] != ','))
		i++;
	while (ft_is_whitespace(str[i]))
		i++;
	while (ft_isdigit(str[i]) || (str[i] == ',' && str[i + 1] != ','))
		i++;
	if (str[i])
	{
		free(win_infos->fc);
		leave(win_infos, ft_strjoin("Error\nIn color string format : ", str),
			-1);
	}
	return (OK);
}

static	int		get_num_color(t_window *win_infos, char *line, int *i)
{
	int	color;

	while (ft_is_whitespace(line[*i]))
		(*i)++;
	color = ft_atoi(&(line[*i]));
	if (color < 0 || color > 255)
		return (ERROR_LIM);
	while (ft_isdigit(line[*i]))
		(*i)++;
	(*i)++;
	return (color);
}

static	int		get_color_from_rgb(int r, int g, int b)
{
	int	rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

static	void	get_color_floor_ceiling(t_window *win_infos, int rgb, int c)
{
	if (c == 'F')
	{
		if (win_infos->color_floor == -20)
			win_infos->color_floor = rgb;
		else
		{
			free(win_infos->fc);
			leave(win_infos, "Error\nMultiple floor colors on file", -1);
		}
	}
	else if (c == 'C')
	{
		if (win_infos->color_ceiling == -20)
			win_infos->color_ceiling = rgb;
		else
		{
			free(win_infos->fc);
			leave(win_infos, "Error\nMultiple ceiling colors on file", -1);
		}
	}
}

int				color_from_string(t_window *win_infos, int first_char_pos,
								char *line, int c)
{
	int	i;
	int	r;
	int	g;
	int	b;
	int	rgb;

	if (!check_line_format(win_infos, first_char_pos, line, c))
		return (ERROR);
	i = first_char_pos + 1;
	while (ft_is_whitespace(line[i]))
		i++;
	if ((r = get_num_color(win_infos, line, &i)) == ERROR_LIM ||
			(g = get_num_color(win_infos, line, &i)) == ERROR_LIM ||
			(b = get_num_color(win_infos, line, &i)) == ERROR_LIM)
	{
		free(win_infos->fc);
		leave(win_infos, ft_strjoin("Error\nColor outside limits : ", line),
			-1);
	}
	rgb = get_color_from_rgb(r, g, b);
	get_color_floor_ceiling(win_infos, rgb, c);
	free(win_infos->fc);
	free(line);
	return (OK);
}
