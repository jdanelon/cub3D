/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 13:49:51 by jdanelon          #+#    #+#             */
/*   Updated: 2021/01/30 14:45:43 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	next_sprite(t_sprite_list *sprites_on_screen,
							t_sprite_list *new, int map_x, int map_y)
{
	while (1)
	{
		if (sprites_on_screen->x == map_x &&
				sprites_on_screen->y == map_y)
		{
			free(new);
			break ;
		}
		if ((sprites_on_screen->x != map_x ||
				sprites_on_screen->y != map_y) &&
				!sprites_on_screen->next)
		{
			ft_lstadd_back((t_list **)(&sprites_on_screen), (t_list *)new);
			break ;
		}
		if (sprites_on_screen->next)
			sprites_on_screen = sprites_on_screen->next;
		else
		{
			free(new);
			break ;
		}
	}
}

void			is_sprite(t_window *win_infos, int map_x, int map_y)
{
	t_sprite_list	*new;
	t_sprite_list	*actual;
	t_sprite_list	save_top;

	new = (t_sprite_list *)malloc(sizeof(t_sprite_list));
	if (new)
	{
		new->x = map_x;
		new->y = map_y;
		new->next = NULL;
	}
	actual = win_infos->sprites_on_screen;
	save_top = *actual;
	if (actual->x == -20 && actual->y == -20)
	{
		actual->x = map_x;
		actual->y = map_y;
		free(new);
	}
	else
		next_sprite(actual, new, map_x, map_y);
	actual = &save_top;
}

void			sort_sprite(t_window *win_infos, t_sprite *sprites,
							int nbr_sprites)
{
	int			i;
	double		distance_one;
	double		distance_two;
	t_sprite	aux;

	i = 0;
	while (i < nbr_sprites && i + 1 != nbr_sprites)
	{
		distance_one = distance(win_infos,
			(sprites[i].x + 0.5) * win_infos->tile_size_x,
			(sprites[i].y + 0.5) * win_infos->tile_size_y);
		distance_two = distance(win_infos,
			(sprites[i + 1].x + 0.5) * win_infos->tile_size_x,
			(sprites[i + 1].y + 0.5) * win_infos->tile_size_y);
		if (distance_one < distance_two)
		{
			aux = sprites[i];
			sprites[i] = sprites[i + 1];
			sprites[i + 1] = aux;
			i = 0;
		}
		else
			i++;
	}
}

t_sprite		*list_to_tab(t_window *win_infos)
{
	t_sprite		*rtn;
	t_sprite_list	*save_top;
	int				count;

	save_top = win_infos->sprites_on_screen;
	count = -1;
	if (!(rtn = (t_sprite *)malloc(sizeof(t_sprite) *
			ft_lstsize((t_list *)win_infos->sprites_on_screen))))
		return (ERROR);
	ft_bzero(rtn, sizeof(t_sprite) *
		ft_lstsize((t_list *)win_infos->sprites_on_screen));
	while (++count > -1)
	{
		if (win_infos->sprites_on_screen)
		{
			rtn[count].x = win_infos->sprites_on_screen->x;
			rtn[count].y = win_infos->sprites_on_screen->y;
		}
		if (win_infos->sprites_on_screen->next)
			win_infos->sprites_on_screen = win_infos->sprites_on_screen->next;
		else
			break ;
	}
	win_infos->sprites_on_screen = save_top;
	return (rtn);
}

int				stock_sprite(t_window *win_infos, char *path)
{
	if (!win_infos->sprite->img_ptr)
	{
		if (!(win_infos->sprite->img_ptr =
				mlx_xpm_file_to_image(win_infos->mlx_ptr, path,
				&win_infos->sprite->width, &win_infos->sprite->height)))
		{
			free(path);
			free(win_infos->fc);
			return (ERROR);
		}
	}
	else
		leave(win_infos, "Error\nMultiple sprites on file", -1);
	win_infos->sprite->data = mlx_get_data_addr(win_infos->sprite->img_ptr,
			&win_infos->sprite->bpp, &win_infos->sprite->size_line,
			&win_infos->sprite->endian);
	free(path);
	free(win_infos->fc);
	return (OK);
}
