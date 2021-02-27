/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:50:19 by jdanelon          #+#    #+#             */
/*   Updated: 2021/02/23 14:39:10 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ESC 65307
# define FORWARD 119
# define BACKWARD 115
# define LEFT 97
# define RIGHT 100
# define CAM_LEFT 65361
# define CAM_RIGHT 65363

# define ERROR_LIM -1
# define ERROR 0
# define OK 1
# define NEXT 2

# define BUFFER_SIZE 128
# define PI 3.14159265358979323846

# include "../libft/libft.h"
# include "utils.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>

typedef	struct	s_geom_line
{
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}				t_geom_line;

typedef	struct	s_sprite
{
	int	x;
	int	y;
}				t_sprite;

typedef	struct	s_sprite_list
{
	int						x;
	int						y;
	struct s_sprite_list	*next;
}				t_sprite_list;

typedef	struct	s_draw_sprite
{
	t_sprite	*sprites;
	int			i;
	double		sprite_x;
	double		sprite_y;
	double		distance;
	double		angle;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			stripe;
	int			y;
	int			d;
	int			tex_x;
	int			tex_y;
	int			color;
	int			totcolor;
}				t_draw_sprite;

typedef	struct	s_line
{
	int	x;
	int	y;
	int	y0;
	int	y1;
	int	tex_x;
	int	tex_y;
}				t_line;

typedef	struct	s_first_chars
{
	int	c0;
	int	c1;
}				t_first_chars;

typedef	struct	s_ray
{
	double	rotation_angle;
	int		horizontal_wall_hit;
	int		vertical_wall_hit;
	double	horizontal_distance;
	double	vertical_distance;
	double	x_step_horizontal;
	double	y_step_horizontal;
	double	x_step_vertical;
	double	y_step_vertical;
	double	x_intercept_horizontal;
	double	y_intercept_horizontal;
	double	x_intercept_vertical;
	double	y_intercept_vertical;
	int		facing_up;
	int		facing_down;
	int		facing_left;
	int		facing_right;
	double	*z_buffer;
}				t_ray;

typedef	struct	s_image
{
	int		width;
	int		height;
	int		size_line;
	int		bpp;
	int		endian;
	void	*img_ptr;
	char	*data;
}				t_image;

typedef	struct	s_map
{
	char			**map;
	const	char	*map_name;
	int				*width;
	int				max_width;
	int				height;
	int				letter;
}				t_map;

typedef	struct	s_player
{
	double	x;
	double	y;
	int		turn_direction;
	int		walk_direction;
	int		move_sideways;
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
}				t_player;

typedef	struct	s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
	int				color_floor;
	int				color_ceiling;
	int				save;
	int				map_description_found;
	int				space_after_map_description_found;
	double			tile_size_x;
	double			tile_size_y;
	double			*ray_distances;
	double			*ray_angles;
	int				*intercept;
	double			*wall_d;
	double			fov_angle;
	double			minimap_scale_factor;
	t_map			*map;
	t_player		*player;
	t_image			*img;
	t_image			**textures;
	t_first_chars	*fc;
	t_image			*sprite;
	t_sprite_list	*sprites_on_screen;
}				t_window;

/*
** cub3d.c & utils
*/
void			leave(t_window *win_infos, char *msg, int errno);
int				create_bmp(t_image *img, char *name);
int				check_map_content(t_window *win_infos, char **map);
void			free_map_copy(t_window *win_infos, char **copy);
int				flood_fill(t_window *win_infos, char **map, int x, int y);
void			rect_minimap(t_window *win_infos, int color, int x, int y);
void			line_ray(t_window *win_infos, double ray_angle, int len);
void			rect(t_window *win_infos, int x, int y, int len_y);
double			normalize_angle(double ray_angle);
double			distance(t_window *win_infos, double x1, double y1);
double			get_relative_distance(t_window *win_infos, t_draw_sprite *ds);
int				sprite_on_fov(t_window *win_infos, t_draw_sprite *ds);
void			line(t_window *win_infos, int x0, int y0, int len);
void			put_ceiling_floor(t_window *win_infos, double strip_height,
									int idx);

/*
** srcs/init_game.c
*/
int				init_game_player(t_window *win_infos);
int				init_game_sprite(t_window *win_infos);
int				init_game_textures(t_window *win_infos, int nbr_textures);
int				init_game_map(t_window *win_infos, const char *map_name);

/*
** srcs/description
*/
int				color_from_string(t_window *win_infos, int first_char_pos,
									char *line, int c);
char			**map_from_string(t_window *win_infos, char *str);
int				path_from_string(t_window *win_infos, int first_char_pos,
									char *line, t_first_chars *fc);
char			*treat_description(t_window *win_infos, const char *map_name);
int				window_size_from_string(t_window *win_infos, char *line);

/*
** srcs/engine/camera.c
*/
void			set_start_camera(t_window *win_infos, double plane_x,
									double plane_y, double dir_x);
void			turn_left(t_window *win_infos);
void			turn_right(t_window *win_infos);

/*
** srcs/engine/image.c
*/
t_image			*new_image(t_window *win_infos, int x_len, int y_len);
void			vertical_line_texture_image(t_window *win_infos,
											t_image *texture, t_line *line,
											double strip_height);
void			pixel_put_to_img(t_image *img, int color, int x, int y);
int				minimap(t_window *win_infos);

/*
** srcs/engine/player.c
*/
void			set_start_position(t_window *win_infos, int cursor,
									char dir, int u);
void			move_forward(t_window *win_infos);
void			move_backward(t_window *win_infos);
void			move_left(t_window *win_infos);
void			move_right(t_window *win_infos);

/*
** srcs/engine/raycasting
*/
int				raycasting(t_window *win_infos);
int				has_wall_at(t_window *win_infos, double x, double y);
double			cast_ray(t_window *win_infos, t_ray *ray, int idx);

/*
** srcs/engine/sprite
*/
void			is_sprite(t_window *win_infos, int map_x, int map_y);
int				stock_sprite(t_window *win_infos, char *path);
void			sort_sprite(t_window *win_infos, t_sprite *sprites,
							int nbr_sprites);
t_sprite		*list_to_tab(t_window *win_infos);
int				draw_sprite(t_window *win_infos);

/*
** srcs/engine/textures
*/
void			texturization(t_window *win_infos, int idx, double ray_angle,
								double strip_height);
int				set_texture(t_window *win_infos, char *path, int index);

/*
** srcs/managers
*/
int				event_key_pressed(int key, void *param);
int				event_key_released(int key, void *param);
int				event_destroy_window(void *param);
int				loop_manager(void *param);
void			free_all(t_window *win_infos, int errno);

#endif
