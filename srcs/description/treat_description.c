/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_description.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:52:53 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 17:37:49 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	int	is_from_path(t_window *win_infos, int first_char, char *line)
{
	win_infos->fc = (t_first_chars *)malloc(sizeof(t_first_chars));
	ft_bzero(win_infos->fc, sizeof(t_first_chars));
	if (line[first_char] && line[first_char + 1])
	{
		win_infos->fc->c0 = line[first_char];
		win_infos->fc->c1 = line[first_char + 1];
	}
	else
	{
		free(win_infos->fc);
		return (NEXT);
	}
	if (win_infos->fc->c0 == 'R')
		return (window_size_from_string(win_infos, line));
	else if (win_infos->fc->c0 == 'N' || win_infos->fc->c0 == 'S' ||
			win_infos->fc->c0 == 'W' || win_infos->fc->c0 == 'E')
		return (path_from_string(win_infos, first_char, line, win_infos->fc));
	else if (win_infos->fc->c0 == 'F' || win_infos->fc->c0 == 'C')
	{
		return (color_from_string(win_infos, first_char,
			line, line[first_char]));
	}
	free(win_infos->fc);
	return (NEXT);
}

static	int	is_map(char **map_string, int first_char, int rtn_gnl, char *line)
{
	char	*save_map_string;

	if (line[first_char] == '0' || line[first_char] == '1' ||
			line[first_char] == '2' || line[first_char] == 'N' ||
			line[first_char] == 'S' || line[first_char] == 'W' ||
			line[first_char] == 'E')
	{
		save_map_string = *map_string;
		*map_string = ft_strjoin(*map_string, line);
		free(save_map_string);
		if (rtn_gnl && line[first_char])
		{
			save_map_string = *map_string;
			*map_string = ft_strjoin(*map_string, "\n");
			free(save_map_string);
		}
		free(line);
		return (OK);
	}
	return (ERROR);
}

static	int	is_other(t_window *win_infos, int first_char, char *line)
{
	if (line[first_char])
	{
		if (line[first_char] != '\n')
			leave(win_infos, ft_strjoin("Error\nUnknown identifier : ", line),
				-1);
	}
	else if (win_infos->map_description_found == 1)
		win_infos->space_after_map_description_found = 1;
	free(line);
	return (OK);
}

static	int	get_infos(t_window *win_infos, char **map_string,
						int rtn_gnl, char *line)
{
	int	rtn_ifp;
	int	first_char;

	first_char = 0;
	while (ft_is_whitespace(line[first_char]))
		first_char++;
	if (win_infos->space_after_map_description_found == 1 && line[first_char])
		leave(win_infos, "Error\nIn map description", -1);
	if (!(rtn_ifp = is_from_path(win_infos, first_char, line)))
	{
		free(line);
		return (ERROR);
	}
	if (rtn_ifp == NEXT)
	{
		if (is_map(map_string, first_char, rtn_gnl, line))
		{
			win_infos->map_description_found = 1;
			return (OK);
		}
		else
			is_other(win_infos, first_char, line);
	}
	return (OK);
}

char		*treat_description(t_window *win_infos, const char *map_name)
{
	int		fd;
	int		rtn_gnl;
	char	*line;
	char	*map_string;

	if ((fd = open(map_name, O_RDONLY)) == -1)
		leave(win_infos, "Error\nCUB file error", -1);
	map_string = (char *)malloc(sizeof(char));
	ft_bzero(map_string, sizeof(char));
	while ((rtn_gnl = get_next_line(fd, &line)) != -1)
	{
		if (line && !get_infos(win_infos, &map_string, rtn_gnl, line))
		{
			free(map_string);
			return (ERROR);
		}
		line = NULL;
		if (rtn_gnl == 0)
			break ;
	}
	free(line);
	return (map_string);
}
