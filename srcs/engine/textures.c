/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:54:08 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 15:03:25 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	int		determine_side(t_window *win_infos, t_line *line,
								double ray_angle)
{
	int	side;
	int	facing_up;
	int	facing_left;

	ray_angle = normalize_angle(ray_angle);
	if (ray_angle > PI && ray_angle < 2 * PI)
		facing_up = 1;
	else
		facing_up = 0;
	if (ray_angle > PI / 2 && ray_angle < 3 * PI / 2)
		facing_left = 1;
	else
		facing_left = 0;
	if (!win_infos->intercept[line->x] && facing_up)
		side = 0;
	else if (!win_infos->intercept[line->x] && !facing_up)
		side = 1;
	else if (win_infos->intercept[line->x] && facing_left)
		side = 2;
	else if (win_infos->intercept[line->x] && !facing_left)
		side = 3;
	return (side);
}

static	void	draw(t_window *win_infos, t_image *img, t_line *line,
						double strip_height)
{
	int		draw_start;
	int		draw_end;

	draw_start = (win_infos->height - strip_height) / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (win_infos->height + strip_height) / 2;
	if (draw_end >= win_infos->height)
		draw_end = win_infos->height - 1;
	line->y0 = draw_start;
	line->y1 = draw_end;
	vertical_line_texture_image(win_infos, img, line, strip_height);
}

void			texturization(t_window *win_infos, int idx, double distance,
							double strip_height)
{
	int		side;
	int		tex_x;
	t_image	*img;
	t_line	*line;

	line = malloc(sizeof(t_line));
	ft_bzero(line, sizeof(t_line));
	line->x = idx;
	side = determine_side(win_infos, line, win_infos->ray_angles[idx]);
	img = win_infos->textures[side];
	if (side == 1 || side == 2)
		win_infos->wall_d[idx] = 1 - win_infos->wall_d[idx];
	if (side == 0 || side == 1)
		win_infos->wall_d[idx] /= win_infos->tile_size_x;
	else
		win_infos->wall_d[idx] /= win_infos->tile_size_y;
	win_infos->wall_d[idx] -= floor(win_infos->wall_d[idx]);
	tex_x = (int)(win_infos->wall_d[idx] * img->width);
	line->tex_x = tex_x;
	draw(win_infos, img, line, strip_height);
	free(line);
}

int				set_texture(t_window *win_infos, char *path, int index)
{
	if (!win_infos->textures[index]->img_ptr)
	{
		if (!(win_infos->textures[index]->img_ptr =
				mlx_xpm_file_to_image(win_infos->mlx_ptr, path,
				&win_infos->textures[index]->width,
				&win_infos->textures[index]->height)))
		{
			free(path);
			free(win_infos->fc);
			return (ERROR);
		}
	}
	else
		leave(win_infos, "Error\nMultiple textures for same identifier on file",
			-1);
	win_infos->textures[index]->data =
		mlx_get_data_addr(win_infos->textures[index]->img_ptr,
							&win_infos->textures[index]->bpp,
							&win_infos->textures[index]->size_line,
							&win_infos->textures[index]->endian);
	free(path);
	free(win_infos->fc);
	return (OK);
}
