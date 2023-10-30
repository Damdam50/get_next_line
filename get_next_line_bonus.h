/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:57:28 by dalebran          #+#    #+#             */
/*   Updated: 2023/10/30 10:59:50 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define MAX_FD 1024

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
void	*ft_memmove(void *dest, const void *src, int n);
char	*read_and_concat(int fd, char *remainder, int *eof);
char	*extract_line(char **remainder);
char	*get_line_from_remainder(char **remainder, int fd);

#endif
