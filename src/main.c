/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:35:21 by radib             #+#    #+#             */
/*   Updated: 2026/04/15 16:32:30 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	find_cub(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = -1;
	while (str[++i] && i <= len - 4)
	{
		if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u'
			&& str[i + 3] == 'b' && str[i + 4] == '\0')
			return (1);
	}
	return (0);
}

void	moving_cam(t_cube **c, int key)
{
	if (key == 65361)
	{
		(*c)->angle -= 15.00;
		if ((*c)->angle < 0)
			(*c)->angle = 360 - ((*c)->angle * -1);
		raycast(c, 0, (*c)->angle);
	}
	else
	{
		(*c)->angle += 15.00;
		(*c)->angle = fmodf((*c)->angle, 360.00);
		raycast(c, 0, (*c)->angle);
	}
	// printf("angle : %f\n", (*c)->angle);
}

void	cleanup(t_cube **c)
{
	t_cube	*z;

	z = *c;
	mlx_clear_window(z->m_ptr, z->w_ptr);
	mlx_destroy_window(z->m_ptr, z->w_ptr);
	mlx_destroy_display(z->m_ptr);
	free(*c);
	exit(0);
}

int	handle_key(int key, t_cube *c)
{
	printf("%d\n", key);
	if (key == 65307)
		cleanup(&c);
	if (key == 122 || key == 115 || key == 113 || key == 100)
		moving(&c, key);
	if (key == 65361 || key == 65363)
		moving_cam(&c, key);
	return (0);
}
//115 bas
//100 droite
//113 gauche
//122 avant
int	cleanup_exit(t_cube *c)
{
	mlx_clear_window(c->m_ptr, c->w_ptr);
	mlx_destroy_window(c->m_ptr, c->w_ptr);
	mlx_destroy_display(c->m_ptr);
	exit(0);
}

int	main(int ac, char **av)
{
	t_parse	*parse;
	t_cube	*c;

	c = malloc(sizeof(t_cube) * 1);
	parse = init_parse();
	if (ac != 2)
		return (print_error("ERROR\nUsage :\n./cube3D [filename].cub\n"));
	if (!find_cub(av[1]))
		return (print_error("ERROR\nMake sure to use a valid .cub file\n"));
	if (get_file_data(av[1], parse))
		return (free_parse(parse), 1);
	if (check_map(parse->map, parse))
		return (free_parse(parse), 1);
	if (init_cube(&c, parse->start, parse->map, parse))
		return (1);
	mlx_hook(c->w_ptr, 17, 1L >> 17, cleanup_exit, c);
	mlx_key_hook(c->w_ptr, handle_key, c);
	render_roof(10000 * 0 + 100 * 20 + 20, &c);
	render_floor(300 * 10000 + 100 * 100 + 50, &c);
	mlx_put_image_to_window(c->m_ptr, c->w_ptr, c->roof_and_ground->img, 0, 0);
	c->displayed_img = init_image(c, c->height, c->width);
	raycast(&c, 0, c->angle);
	mlx_loop(c->m_ptr);
	return (0);
}
// ESC	65307
// W	119
// A	97
// S	115
// D	100
// UP	65362
// DOWN	65364
// LEFT	65361
// RIGHT	65363