/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhanuise <fhanuise@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:47:28 by fhanuise          #+#    #+#             */
/*   Updated: 2026/04/15 17:22:15 by fhanuise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	check_player(t_parse *parse, char c, int i, int j)
{
	if (!parse->player)
	{
		parse->player = 1;
		parse->start = c;
		parse->pos_x = (float) i + 0.5;
		parse->pos_y = (float) j + 0.5;
	}
	else
		return(print_error("ERROR\nToo much player in map\n"));
	return (0);
}

int char_not_valid(char **str, t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == 'N' || str[i][j] == 'S'
				|| str[i][j] == 'E' || str[i][j] == 'W')
			{
				if (check_player(parse, str[i][j], i, j))
					return (1);
			}
			else if (str[i][j] != '0' && str[i][j] != '1'
				&& str[i][j] != ' ' && str[i][j] != '\n')
				return (print_error("ERROR\nInvalid character in map\n"));
			j++;
		}
		i++;
	}
	if (!parse->player)
		return (print_error("ERROR\nNo player in map\n"));
	return (0);
}

static int    is_surrounded(char **map, int x, int y, int rows)
{
	if (y == 0 || y == rows - 1)
		return (1);
	if (x == 0)
		return (1);
	if (!map[y - 1] || !map[y + 1])
		return (1);
	if (map[y][x - 1] == ' ' || map[y][x - 1] == '\0')
		return (1);
	if (map[y][x + 1] == ' ' || map[y][x + 1] == '\0')
		return (1);
	if ((int)ft_strlen(map[y - 1]) <= x || map[y - 1][x] == ' ')
		return (1);
	if ((int)ft_strlen(map[y + 1]) <= x || map[y + 1][x] == ' ')
		return (1);
	if ((int)ft_strlen(map[y - 1]) <= x - 1 || map[y - 1][x - 1] == ' ')
		return (1);
	if ((int)ft_strlen(map[y - 1]) <= x + 1 || map[y - 1][x + 1] == ' ')
		return (1);
	if ((int)ft_strlen(map[y + 1]) <= x - 1 || map[y + 1][x - 1] == ' ')
		return (1);
	if ((int)ft_strlen(map[y + 1]) <= x + 1 || map[y + 1][x + 1] == ' ')
		return (1);
	return (0);
}

static int    is_walkable(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int    invalid_map(char **map)
{
	int rows;
	int i;
	int j;

	rows = 0;
	while (map[rows])
		rows++;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (is_walkable(map[i][j]))
			{
				if (is_surrounded(map, j, i, rows))
					return (print_error("ERROR\nMap is not closed\n"));
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(char **map, t_parse *parse)
{
	if (char_not_valid(map, parse) || invalid_map(map))
		return (1);
	return (0);
}
