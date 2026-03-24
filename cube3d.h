/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:03:09 by radib             #+#    #+#             */
/*   Updated: 2026/03/24 16:46:48 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../minilibx/mlx.h"
# include "math.h"
# include "../libft/libft.h"

// temp include
#include <string.h>

# define M_PI           3.14159265358979323846

enum wall
{
	wall_north,
	wall_east,
	wall_south,
	wall_west
};

typedef struct quadrants
{
	int	top_rx;
	int	top_ry;
	int	bot_rx;
	int	bot_ry;
	int	bot_lx;
	int	bot_ly;
	int	top_lx;
	int	top_ly;
}	t_quadrants;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct raydata
{
	float	wall_pixel;
	float	dist;
	int		x_mult;
	int		y_mult;
	float	cur_rpos_x;
	float	cur_rpos_y;
	t_img	*wall;
}	t_ray;

typedef struct cube
{
	float	pos_x;
	float	pos_y;
	float	angle;
	char	**map;
	int		width;
	int		height;
	int		fps;
	float	fov;
	void	*m_ptr;
	void	*w_ptr;
	t_ray	**raydata;
	t_img	*displayed_img;
	t_img	*roof_and_ground;
	t_img	*wall_n;
	t_img	*wall_s;
	t_img	*wall_e;
	t_img	*wall_w;
}			t_cube;
// init
void	init_cube(t_cube **c, char angle, char **map);
void	moving(t_cube **c, int key);
void	render_roof(int color, t_cube **c);
void	render_floor(int color, t_cube **c);
t_img	*init_image(t_cube *p, int height, int width);
void	put_pixel_to_image(t_img *img, int x, int y, int color);
void	raycast(t_cube **c, int i, float angles);
float	deg_to_rad(float deg);

#endif
