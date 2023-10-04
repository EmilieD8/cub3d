/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:07:00 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/19 10:18:15 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*memmovegnl(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (dest[i] != '\0')
		dest[i++] = '\0';
	return (dest);
}

char	*splitmp(char *tmp)
{
	char	*line;
	size_t	i;
	size_t	length;

	if (!tmp)
		return (NULL);
	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	length = i + 1;
	line = malloc(sizeof(char) * length + 1);
	if (!line)
		return (NULL);
	memcpyb(line, tmp, length);
	line[length] = '\0';
	memmovegnl(tmp, &tmp[length], ft_strlen(&tmp[i]));
	return (line);
}

char	*readtmp(int fd, char *tmp)
{
	char	*buffer;
	int		nread;

	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	while (searchn(tmp) != 1)
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread == -1)
		{
			if (tmp)
				free(tmp);
			return (free(buffer), NULL);
		}
		if (nread == 0)
			break ;
		buffer[nread] = '\0';
		tmp = join_buffer_tmp(tmp, buffer);
		if (tmp == NULL)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	tmp = readtmp(fd, tmp);
	if (!tmp)
		return (NULL);
	line = splitmp(tmp);
	if (!line)
		return (free(line), NULL);
	if (*tmp == '\0')
	{
		free(tmp);
		tmp = NULL;
	}
	return (line);
}
