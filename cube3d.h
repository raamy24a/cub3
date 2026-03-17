/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:03:09 by radib             #+#    #+#             */
/*   Updated: 2026/03/17 16:22:21 by radib            ###   ########.fr       */
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
	int		wall;
	float	wall_pixel;
	float	dist;
	float	cur_rpos_x;
	float	cur_rpos_y;
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
	void	*m_ptr;
	void	*w_ptr;
	t_ray	**raydata;
	t_img	*displayed_img;
	t_img	*roof_and_ground;
}			t_cube;
// init
void	init_cube(t_cube **c, char angle, char **map);
void	moving(t_cube **c, int key);
void	render_roof(int color, t_cube **c);
void	render_floor(int color, t_cube **c);
t_img	*init_image(t_cube *p, int height, int width);
void	put_pixel_to_image(t_img *img, int x, int y, int color);
void	raycast(t_cube **c, int i, float angles);

#endif
