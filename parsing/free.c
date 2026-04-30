/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhanuise <fhanuise@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:38:44 by fhanuise          #+#    #+#             */
/*   Updated: 2026/04/30 13:53:02 by fhanuise         ###   ########.fr       */
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
	if (parse->EA_wall)
		free(parse->EA_wall);
	if (parse->NO_wall)
		free(parse->NO_wall);
	if (parse->SO_wall)
		free(parse->SO_wall);
	if (parse->WE_wall)
		free(parse->WE_wall);
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