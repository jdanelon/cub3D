/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:53:27 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/26 11:32:08 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void			pixel_put_to_img(t_image *img, int color, int x, int y)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*((unsigned int *)dst) = color;
}

static	void	texture_on_image(t_window *win_infos, t_image *texture,
									t_line *line, double strip_height)
{
	line->tex_y = (line->y - (int)(win_infos->height - strip_height) / 2) *
		texture->height / strip_height;
	win_infos->img->data[line->y * win_infos->img->size_line +
		line->x * win_infos->img->bpp / 8] = texture->data[line->tex_y *
		texture->size_line + line->tex_x * (texture->bpp / 8)];
	win_infos->img->data[line->y * win_infos->img->size_line +
		line->x * win_infos->img->bpp / 8 + 1] = texture->data[line->tex_y *
		texture->size_line + line->tex_x * (texture->bpp / 8) + 1];
	win_infos->img->data[line->y * win_infos->img->size_line +
		line->x * win_infos->img->bpp / 8 + 2] = texture->data[line->tex_y *
		texture->size_line + line->tex_x * (texture->bpp / 8) + 2];
}

void			vertical_line_texture_image(t_window *win_infos,
												t_image *texture,
												t_line *line,
												double strip_height)
{
	int	y_max;

	line->y = line->y0;
	y_max = line->y1;
	while (line->y < y_max)
	{
		texture_on_image(win_infos, texture, line, strip_height);
		line->y++;
	}
}

t_image			*new_image(t_window *win_infos, int x_len, int y_len)
{
	t_image	*img;

	if (!(img = (t_image *)malloc(sizeof(t_image))))
		return ((void *)0);
	ft_bzero(img, sizeof(t_image));
	if (!(img->img_ptr = mlx_new_image(win_infos->mlx_ptr, x_len, y_len)))
		return ((void *)0);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp,
									&img->size_line, &img->endian);
	img->width = x_len;
	img->height = y_len;
	return (img);
}
