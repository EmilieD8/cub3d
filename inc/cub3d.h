/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:43:39 by mschaub           #+#    #+#             */
/*   Updated: 2023/10/02 14:25:54 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "structs.h"
# include <fcntl.h>
# include <stdbool.h>

/* Defined errors */

# define ARGS_ERR		"Wrong arguments!\n"
# define MLX_ERR		"MLX could not be created\n"
# define WIN_ERR		"Window could not be created\n"
# define IMG_ERR		"Image could not be created\n"
# define MAP_ERR		"Invalid map\n"
# define CUB_ERR		"Not a .cub file\n"
# define READ_ERR		"File cannot be read\n"

/* Defined key values */
# define UP     65362
# define DOWN   65364
# define LEFT   65361
# define RIGHT  65363
# define KEY_W   122
# define KEY_S   115
# define KEY_A   113
# define KEY_D   100
# define ESC     65307
# define KEY_Q   97

/* Dimensions */

# define WIDTH			1280
# define HEIGHT			800
# define BLOCK			64
# define FOV			60.0

/* Directions*/
# define NORTH             0
# define SOUTH             1
# define EAST              2
# define WEST              3
# define DOOR              4

/* ----- Functions ----- */

/* Main */
void		start_whole_game(t_master *master);
void		draw_menu(t_master *master);
void		keys_menu(mlx_key_data_t keydata, void *param);

/* Initialization */
t_master	*ft_init(t_master *master);
t_master	*init_ray(t_master *master);
void		init_map(t_master *master);
void		init_player(t_master *master);

/* Map parsing */
int			check_map(t_master *master);
int			is_color(t_master *master, char *string);
int			get_color_numbers(t_master *master, char **numbers, int type);
int			check_input_file(t_master *master, int fd);
int			check_valid_char_map(t_master *master);
int			find_player_position(t_master *master);
int			find_dir(char c);
int			check_extra_lines(char *string);
void		find_biggest_line(t_map *map);
size_t		find_biggest_line_bis(char **map, int index);
void		free_two_strings(char *one, char *two);
int			is_elements(t_master *master, char *string);

/* Raycasting */

void		ft_raycast(void *param);
void		assign_values(t_master *master, int cols);
void		assign_textures(t_master *master, int cols, int map_x, int map_y);

/* Rendering */
uint32_t	*get_color(mlx_texture_t *texture, t_master *master);
u_int32_t	color_pixel(u_int32_t *pixel);
t_texture	*ft_textures(t_master *master);
void		ft_render(t_master *master);
void		draw_minimap(t_master *master);
void		draw_player(t_master *master);
void		draw_ray_minimap(t_master *master);
void		draw_bottle(t_master *master);
void		floor_ceil(t_master *master);
void		draw_ray(int cols, t_master *master, mlx_image_t img);
/* Moving */
void		change_angle(t_master *master);
void		change_position(t_master *master, t_pos new, double steps);
void		update_player_position(t_master *master);
void		set_keys(mlx_key_data_t keydata, void *param);

/* Closing, Freeing & Error Management */
void		terminate_game(t_master *master);
int			close_window(t_master *master);
int			ft_error(t_master *master, char *str, int i);
void		free_array(char **array);

/* Utils */
int			get_rgba(int r, int g, int b);
size_t		ft_iscub(char *file);
void		textures_helper(t_master *master, t_texture *textures);
void		draw_helper(t_master *master, int i, int cols, mlx_image_t img);

#endif
