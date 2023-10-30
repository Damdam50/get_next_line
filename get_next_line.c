/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:59:12 by dalebran          #+#    #+#             */
/*   Updated: 2023/10/30 06:55:57 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_concat(int fd, char *remainder);

void	*ft_memmove(void *dest, const void *src, int n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	if (s < d)
	{
		s += n;
		d += n;
		while (n--)
		{
			*(--d) = *(--s);
		}
	}
	else
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	return (dest);
}

static char	*read_and_concat(int fd, char *remainder)
{
	char	*buffer;
	int		bytes_read;
	char	*tmp;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(remainder);
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	tmp = ft_strjoin(remainder, buffer);
	free(remainder);
	free(buffer);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*newline_pos;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	newline_pos = ft_strchr(remainder, '\n');
	while (!newline_pos)
	{
		remainder = read_and_concat(fd, remainder);
		if (!remainder)
			return (NULL);
		newline_pos = ft_strchr(remainder, '\n');
	}
	if (newline_pos)
	{
		line = ft_substr(remainder, 0, newline_pos - remainder + 1);
		ft_memmove(remainder, newline_pos + 1, ft_strlen(newline_pos + 1) + 1);
	}
	else if (*remainder)
	{
		line = ft_strdup(remainder);
		*remainder = '\0';
	}
	else
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	return (line);
}