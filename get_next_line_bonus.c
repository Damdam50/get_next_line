/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:59:12 by dalebran          #+#    #+#             */
/*   Updated: 2023/10/30 11:02:24 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*read_and_concat(int fd, char *remainder, int *eof)
{
	char	*buffer;
	int		bytes_read;
	char	*tmp;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (bytes_read == 0)
	{
		*eof = 1;
		free(buffer);
		return (remainder);
	}
	buffer[bytes_read] = '\0';
	tmp = ft_strjoin(remainder, buffer);
	free(remainder);
	free(buffer);
	return (tmp);
}

char	*extract_line(char **remainder)
{
	char	*newline_pos;
	char	*line;

	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		line = ft_substr(*remainder, 0, newline_pos - *remainder + 1);
		ft_memmove(*remainder, newline_pos + 1, ft_strlen(newline_pos + 1) + 1);
	}
	else
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}
	return (line);
}

char	*get_line_from_remainder(char **remainder, int fd)
{
	char	*newline_pos;
	int		eof;

	newline_pos = ft_strchr(*remainder, '\n');
	eof = 0;
	while (!newline_pos && !eof)
	{
		*remainder = read_and_concat(fd, *remainder, &eof);
		if (!*remainder)
			return (NULL);
		newline_pos = ft_strchr(*remainder, '\n');
	}
	if (!newline_pos && !**remainder)
	{
		free(*remainder);
		*remainder = NULL;
		return (NULL);
	}
	return (extract_line(remainder));
}

char	*get_next_line(int fd)
{
	static char	*remainder[MAX_FD];

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (remainder[fd])
		{
			free(remainder[fd]);
			remainder[fd] = NULL;
		}
		return (NULL);
	}
	if (!remainder[fd])
		remainder[fd] = ft_strdup("");
	return (get_line_from_remainder(&remainder[fd], fd));
}
