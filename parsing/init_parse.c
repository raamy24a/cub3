/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:19:38 by fhanuise          #+#    #+#             */
/*   Updated: 2026/05/19 17:12:50 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

t_img	*init_image(t_cube *p, int height, int width)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	img->img = mlx_new_image(p->m_ptr, height, width);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

t_img	*init_image_xpm(t_cube **c, char *path_to_image)
{
	t_img	*img;
	int		height;
	int		width;
	t_cube	*p;

	p = *c;
	height = 0;
	width = 0;
	img = malloc(sizeof(t_img));
	img->img = mlx_xpm_file_to_image(p->m_ptr, path_to_image, &width, &height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->height = height;
	img->width = width;
	return (img);
}

int	put_wall_images_to_struct(t_cube **c, t_parse *parse)
{
	t_cube	*p;

	p = (*c);
	p->wall_e = init_image_xpm(c, parse->ea_wall);
	if (!p->wall_e)
		return (free_img_to_struct(*c), 1);
	p->wall_s = init_image_xpm(c, parse->so_wall);
	if (!p->wall_s)
		return (free_img_to_struct(*c), 1);
	p->wall_w = init_image_xpm(c, parse->we_wall);
	if (!p->wall_w)
		return (free_img_to_struct(*c), 1);
	p->wall_n = init_image_xpm(c, parse->no_wall);
	if (!p->wall_n)
		return (free_img_to_struct(*c), 1);
	return (0);
}

t_parse	*init_parse(void)
{
	t_parse	*p;

	p = malloc(sizeof(t_parse) * 1);
	p->ceiling = NULL;
	p->floor = NULL;
	p->map = NULL;
	p->player = 0;
	p->no_wall = NULL;
	p->ea_wall = NULL;
	p->so_wall = NULL;
	p->we_wall = NULL;
	return (p);
}

int	init_cube(t_cube **c, char angle, char **map, t_parse *p)
{
	(*c)->width = 1080;
	(*c)->height = 1080;
	(*c)->parsing = p;
	(*c)->angle = angle_calculator(angle);
	(*c)->m_ptr = mlx_init();
	if (put_wall_images_to_struct(c, p))
		return (print_error("Error:\nUnable to load texture\n"));
	(*c)->fov = 66.00f;
	(*c)->pos_x = p->pos_x;
	(*c)->pos_y = p->pos_y;
	(*c)->w_ptr = mlx_new_window((*c)->m_ptr,
			(*c)->width, (*c)->height, "Cube");
	(*c)->map = map;
	(*c)->floor = *p->floor;
	(*c)->roof = *p->ceiling;
	(*c)->floor = create_rgb(p->ceiling[0], p->ceiling[1], p->ceiling[2]);
	(*c)->roof = create_rgb(p->floor[0], p->floor[1], p->floor[2]);
	(*c)->raydata = ft_calloc(1, sizeof(t_ray));
	(*c)->roof_and_ground = init_image((*c), (*c)->height, (*c)->width);
	
	return (0);
}
