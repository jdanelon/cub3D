/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:52:06 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/31 12:54:16 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	int		data_to_bitmap(t_image *img, int fd)
{
	int		i;

	i = img->width * img->height - 1;
	while (i >= 0)
	{
		write(fd, &img->data[i * img->bpp / 8], 4);
		i--;
	}
	return (OK);
}

static	void	mirror_vertical_pixel(t_image *img, int line_idx, int *e, int f)
{
	char	save;
	int		k;

	k = 3;
	while (k >= 0)
	{
		save = img->data[*e + (line_idx * img->size_line)];
		img->data[*e + (line_idx * img->size_line)] =
			img->data[f - k + (line_idx * img->size_line - 1)];
		img->data[f - k + (line_idx * img->size_line - 1)] = save;
		k--;
		*e = *e + 1;
	}
}

static	int		mirror_vertical_image(t_image *img)
{
	int	line_idx;
	int	e;
	int	f;

	line_idx = 0;
	while (line_idx < img->height)
	{
		e = 0;
		f = img->size_line;
		while (e < f && e != f)
		{
			mirror_vertical_pixel(img, line_idx, &e, f);
			f -= 4;
		}
		line_idx++;
	}
	return (OK);
}

static	int		bitmap_info_header(t_image *img, int fd)
{
	int	header_infos_size;
	int	plane_nbr;
	int	o_count;

	header_infos_size = 40;
	plane_nbr = 1;
	write(fd, &header_infos_size, 4);
	write(fd, &img->width, 4);
	write(fd, &img->height, 4);
	write(fd, &plane_nbr, 2);
	write(fd, &img->bpp, 2);
	o_count = 0;
	while (o_count < 28)
	{
		write(fd, "\0", 1);
		o_count++;
	}
	return (OK);
}

int				create_bmp(t_image *img, char *name)
{
	int	fd;
	int	file_size;
	int	first_pixel;

	name = ft_strjoin(name, ".bmp");
	fd = open(name, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0x777);
	if (fd > 0)
	{
		file_size = 14 + 40 + 4 + (img->width * img->height) * 4;
		first_pixel = 14 + 40 + 4;
		write(fd, "BM", 2);
		write(fd, &file_size, 4);
		write(fd, "\0\0\0\0", 4);
		write(fd, &first_pixel, 4);
		bitmap_info_header(img, fd);
		mirror_vertical_image(img);
		data_to_bitmap(img, fd);
		close(fd);
	}
	free(name);
	return (OK);
}
