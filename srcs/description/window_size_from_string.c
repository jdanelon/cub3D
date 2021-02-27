/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_size_from_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:53:00 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 17:52:49 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	int		check_line_format(char *str)
{
	int	i;

	i = 0;
	while (ft_is_whitespace(str[i]))
		i++;
	if (!str || str[i] != 'R' || str[i + 1] != ' ')
		return (ERROR);
	i++;
	while (ft_is_whitespace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (ERROR);
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_is_whitespace(str[i]))
		return (ERROR);
	while (ft_is_whitespace(str[i]))
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (ft_is_whitespace(str[i]))
		i++;
	if (!ft_is_whitespace(str[i]) && str[i])
		return (ERROR);
	return (OK);
}

static	int		get_size(char *str, int start)
{
	int ret;

	ret = ft_atoi(&str[start]);
	return (ret);
}

static	void	get_width_height(t_window *win_infos, char *line, int *i)
{
	int	max_width;
	int	max_height;

	win_infos->width = get_size(line, *i);
	while (ft_isdigit(line[*i]))
		(*i)++;
	while (ft_is_whitespace(line[*i]))
		(*i)++;
	win_infos->height = get_size(line, *i);
	mlx_get_screen_size(win_infos->mlx_ptr, &max_width, &max_height);
	if (win_infos->width > max_width)
		win_infos->width = max_width;
	if (win_infos->height > max_height)
		win_infos->height = max_height;
	if (!win_infos->width || !win_infos->height)
	{
		free(win_infos->fc);
		leave(win_infos, "Error\nResolution cannot be zero", -1);
	}
}

int				window_size_from_string(t_window *win_infos, char *line)
{
	int	i;
	int	max_width;
	int	max_height;

	if (!check_line_format(line))
	{
		free(win_infos->fc);
		leave(win_infos, ft_strjoin("Error\nIn line format : ", line), -1);
	}
	i = 0;
	while (ft_is_whitespace(line[i]))
		i++;
	i++;
	while (ft_is_whitespace(line[i]))
		i++;
	if (win_infos->width == -20 && win_infos->height == -20)
		get_width_height(win_infos, line, &i);
	else
	{
		free(win_infos->fc);
		leave(win_infos, "Error\nMultiple resolutions on file", -1);
	}
	free(win_infos->fc);
	free(line);
	return (OK);
}
