/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:31:17 by radib             #+#    #+#             */
/*   Updated: 2025/06/10 16:12:02 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strrchr_b(char *s)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s || s[0] == '\0')
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		result = malloc(sizeof(char) * (i + 2));
	else
		result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	j = 0;
	while (j < i)
	{
		result[j] = s[j];
		j++;
	}
	if (s[i] == '\n')
		result[i++] = '\n';
	result[i] = '\0';
	return (result);
}

char	*ft_strrchr_a(char *s, char *new_stash)
{
	size_t	i;

	if (!s || s[0] == '\0')
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n' && s[i + 1] != '\0')
		return (ft_strcpy(new_stash, &s[i + 1]));
	return (ft_strcpy(new_stash, "\0"));
}

size_t	ft_pstrlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_strjoin;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str_strjoin = malloc(sizeof(char) * (ft_pstrlen(s1) + ft_pstrlen(s2) + 1));
	if (!str_strjoin)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_strjoin[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str_strjoin[i++] = s2[j++];
	str_strjoin[i] = '\0';
	return (str_strjoin);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (src[0] == '\0')
	{
		dest[0] = '\0';
		return (dest);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
