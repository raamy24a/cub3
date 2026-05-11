/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:38:44 by fhanuise          #+#    #+#             */
/*   Updated: 2026/05/11 13:04:41 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	free_parse(t_parse *parse)
{
	if (parse)
	{
		if (parse->floor)
			free(parse->floor);
		if (parse->ceiling)
			free(parse->ceiling);
		if (parse->map)
			free_tab(parse->map);
		free_img(parse);
		free(parse);
	}
}

void	free_img(t_parse *parse)
{
	if (parse->ea_wall)
		free(parse->ea_wall);
	if (parse->no_wall)
		free(parse->no_wall);
	if (parse->so_wall)
		free(parse->so_wall);
	if (parse->we_wall)
		free(parse->we_wall);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_struct(t_parse *parse, t_cube *c)
{
	free_parse(parse);
	if (c->m_ptr)
	{
		mlx_destroy_display(c->m_ptr);
		free(c->m_ptr);
	}
	free(c);
}
