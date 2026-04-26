/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhanuise <fhanuise@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:08:21 by fhanuise          #+#    #+#             */
/*   Updated: 2026/04/09 13:39:46 by fhanuise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
// #include "../libft/libft.h"

int	*fill_rgb(char *str)
{
	int		*rgb;
	char	**split;
	int		i;

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (NULL);
	split = ft_split(str, ',');
	if (!split)
		return (free(rgb), NULL);
	i = 0;
	while (i < 3)
	{
		if (!split[i])
			return (free(rgb), free_tab(split), NULL);
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free(rgb), free_tab(split), NULL);
		i++;
	}
	free_tab(split);
	return (rgb);
}

char	*fill_data(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (is_space(str[i]))
		i++;
	j = ft_strlen(str + i);
	while (j > 0 && is_space(str[i + j - 1]))
		j--;
	return (ft_substr(str, i, j));
}

void	is_data(char *str, t_parse *parse)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == 'C' && str[i + 1] == ' ')
		parse->ceiling = fill_rgb(str + i + 2);
	else if (str[i] == 'F' && str[i + 1] == ' ')
		parse->floor = fill_rgb(str + i + 2);
	else if (str[i] == 'N' && (str[i + 1] && str[i + 1] == 'O') && (str[i + 2]
		&& str[i + 2] ==' '))
		parse->NO_wall = fill_data(str + i + 3);
	else if (str[i] == 'S' && (str[i + 1] && str[i + 1] == 'O') && (str[i + 2]
		&& str[i + 2] ==' '))
		parse->SO_wall = fill_data(str + i + 3);
	else if (str[i] == 'W' && (str[i + 1] && str[i + 1] == 'E') && (str[i + 2]
		&& str[i + 2] ==' '))
		parse->WE_wall = fill_data(str + i + 3);
	else if (str[i] == 'E' && (str[i + 1] && str[i + 1] == 'A') && (str[i + 2]
		&& str[i + 2] ==' '))
		parse->EA_wall = fill_data(str + i + 3);
}

char	**parse_map(char *fd, int start)
{
	int		count;

	count = count_map_length(fd, start);
	if (count == 0)
		return (NULL);
	return (alloc_map(fd, start, count));
}

int	get_file_data(char *file, t_parse *parse)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("ERROR \nCouldn't open the file\n"));
	line = get_next_line(fd);
	count = 0;
	while (line && !is_map_line(line))
	{
		if (line[0] != '\n')
			is_data(line, parse);
		free(line);
		count++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	parse->map = parse_map(file, count);
	return (valid_parse(parse));
}
