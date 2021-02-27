/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_from_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:50:51 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/29 19:55:28 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	int	check_line_format(char *str)
{
	int	i;

	i = 0;
	while (ft_is_whitespace(str[i]))
		i++;
	if (str[i] != 'N' && str[i] != 'S' && str[i] != 'W' && str[i] != 'E')
		return (ERROR);
	i++;
	if (str[i] != 'O' && str[i] != 'E' &&
			str[i] != 'A' && !ft_is_whitespace(str[i]))
		return (ERROR);
	i++;
	while (ft_is_whitespace(str[i]))
		i++;
	if (str[i] != '.' && str[i + 1] != '/')
		return (ERROR);
	while (ft_isprint(str[i]) && !ft_is_whitespace(str[i]) && str[i])
		i++;
	if (!ft_is_whitespace(str[i]) && str[i])
		return (ERROR);
	while (ft_is_whitespace(str[i]))
		i++;
	return (str[i] ? ERROR : OK);
}

static	int	get_size(char *str, int start)
{
	int	ret;

	ret = 0;
	while (ft_isprint(str[start + ret]) && !ft_is_whitespace(str[start + ret]))
		ret++;
	return (ret);
}

static	int	file_exists(const char *file_name)
{
	int	fd;
	int	file_name_len;

	file_name_len = ft_strlen(file_name);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (ERROR);
	if (file_name[file_name_len - 4] != '.' ||
			file_name[file_name_len - 3] != 'x' ||
			file_name[file_name_len - 2] != 'p' ||
			file_name[file_name_len - 1] != 'm')
		return (ERROR);
	return (OK);
}

static	int	redirect_textures_sprites(t_window *win_infos, char *path,
										t_first_chars *fc)
{
	if (fc->c0 == 'N' && fc->c1 == 'O')
		return (set_texture(win_infos, path, 0));
	else if (fc->c0 == 'S' && fc->c1 == 'O')
		return (set_texture(win_infos, path, 1));
	else if (fc->c0 == 'W' && fc->c1 == 'E')
		return (set_texture(win_infos, path, 2));
	else if (fc->c0 == 'E' && fc->c1 == 'A')
		return (set_texture(win_infos, path, 3));
	else if (fc->c0 == 'S' && fc->c1 == ' ')
		return (stock_sprite(win_infos, path));
	return (OK);
}

int			path_from_string(t_window *win_infos, int first_char_pos,
						char *line, t_first_chars *fc)
{
	int		i;
	char	*path;

	if (!check_line_format(line))
		leave(win_infos, ft_strjoin("Error\nIn line format : ", line), -1);
	i = (line[first_char_pos + 1] == ' ' ?
		first_char_pos + 2 : first_char_pos + 3);
	while (ft_is_whitespace(line[i]))
		i++;
	if (!(path = ft_substr(line, i, get_size(line, i))) || !file_exists(path))
	{
		free(win_infos->fc);
		leave(win_infos, ft_strjoin("Error\nInvalid path : ", line), -1);
	}
	free(line);
	return (redirect_textures_sprites(win_infos, path, fc));
}
