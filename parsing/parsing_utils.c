/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhanuise <fhanuise@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:06:10 by fhanuise          #+#    #+#             */
/*   Updated: 2026/04/30 14:35:48 by fhanuise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' ||
		c == '\v')
		return (1);
	return (0);
}

int is_map_line(char *line)
{
	int i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	count_map_length(char *file, int start)
{
	int		fd;
	char	*line;
	int		i;
	int		count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i >= start)
			count++;
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
    return (count);
}

char	**alloc_map(char *file, int start, int count)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;
	int		j;

	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	i = -1;
	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (++i >= start)
			map[j++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	map[j] = NULL;
	close(fd);
	return (map);
}

int	 createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
